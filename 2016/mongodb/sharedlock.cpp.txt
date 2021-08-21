/*
 * This is the complete and accurate answer to the white board question posed by second interviewer.
 * The program below demonstrates possible implementation of read-write or exclusive-shared lock,
 * somewhat similar to what can be achieved by using the following POSIX API:
 *
 * pthread_rwlock_init
 * pthread_rwlock_wrlock
 * pthread_rwlock_rdlock
 * pthread_rwlock_unlock
 * pthread_rwlock_destroy
 *
 * The following rules were used to implement this exclusive-shared lock functionality:
 *
 * 1) Writer's or exclusive lock blocks all other writer's or reader's threads from entry to 
 *  the locked region.
 * 2) Reader's lock only blocks writer's threads from entry to the locked region, readers's
 *  threads are free to enter to the guarded region unless writer's lock is detected. 
 * 3) If writer's thread locks the guarded region then all reader's thread will be blocked on
 *  conditional variable (a combination of writer's lock presence and non-zero shared lock 
 *  counter).
 * 4) Any thread that calls common unlock routine will unlock writer's thread lock (as only writer's
 *  thread can enter when readers are blocked and reader's threads also need ito unlock writer's lock)
 *  and unblocks all reader's threads previously blocked by conditional variable. Unblocked threads
 *  however will re-evaluate the condition and only proceed if either writer's lock is not detected
 *  or writer's lock was posted by reader's thread which is being unblocked otherwise they will
 *  continue to wait.
 *
 * Please note that the detection of writer's lock is realized via pthread_mutex_trylock call, so 
 * we can preemptively acquire writer's lock.
 *
 * I also wrote simple test harness that creates 100 threads, 10 of them are writers, 90 are the 
 * readers. I ran test on octacore cpu to check the implementation. To simulate possible contention of 
 * reader's locks and subsequent writer's lock starvation I used POSIX barriers to stampede threads on
 * the entry to readers lock.
 *
 * You can compile this program with: 
 * [vtsozik@SR71 mongodb]$ g++ sharedlock.cpp -lpthread
 * And run it with:
 * [vtsozik@SR71 mongodb]$ ./a.out
 *
 * Thank you in advance for your consideration, valuable comments or suggestions,
 *  Vadim.
 */

#include <iostream>
#include <pthread.h>
using namespace std;

class RWLock {

 /* Read or shared lock */
 pthread_mutex_t m_pmrl;
 /* Write or exclusive lock */
 pthread_mutex_t m_pmwl;
 /* Conditional variable */
 pthread_cond_t m_pcv;
 /* Shared lock count */
 size_t m_stlc;

 /*
 * We don't want accidentally destroy single mutex
 * or conditional variable twice and leak the original
 * instance
 */
 RWLock(const RWLock&) {}
 RWLock& operator=(const RWLock&) {}

 public:

 /*
 * We do need a constructor to initialize the mutexes,
 * conditional variable and shared counter
 */
 RWLock() : m_stlc(0) {
  pthread_mutex_init(&m_pmrl, NULL);
  pthread_mutex_init(&m_pmwl, NULL);
  pthread_cond_init(&m_pcv, NULL);
 }

 /*
 * Destructor comes handy as we need to destroy 
 * these memeber variables at the end
 */
 ~RWLock() {
  pthread_cond_destroy(&m_pcv);
  pthread_mutex_destroy(&m_pmwl);
  pthread_mutex_destroy(&m_pmrl);
 }

 /*
 * Unique or write lock locking routine implementation
 */
 int WRLock() {
  return pthread_mutex_lock(&m_pmwl);
 }

 /*
 * Shared or read lock locking routine implementation
 */
 int RDLock() {
  int r = pthread_mutex_lock(&m_pmrl);
  if(!r) { 
   if(pthread_mutex_trylock(&m_pmwl)) {
    ++m_stlc;
    do {
     r = pthread_cond_wait(&m_pcv, &m_pmrl);
    } while(!r && (pthread_mutex_trylock(&m_pmwl) && m_stlc > 0));
   }
   if(!r) {
    r = pthread_mutex_unlock(&m_pmrl);
   }
  }
  return r;
 }

 /*
 * Common unlock routine implementation
 */
 int RWUnlock() {
  int r = pthread_mutex_lock(&m_pmrl);
  if(!r) {
   if(pthread_mutex_trylock(&m_pmwl)) {
    if(m_stlc > 0) {
     --m_stlc;
     r = pthread_cond_broadcast(&m_pcv);
    }
   }
   if(!r) {
    r = pthread_mutex_unlock(&m_pmwl);
   }
   if(!r) {
    r = pthread_mutex_unlock(&m_pmrl); 
   }
  } 
  return r;
 }

};

/*
 * Test harness
 */

#include <assert.h>
#include <unistd.h>

#define NUMBER_OF_THREADS 100
#define READ_WRITE_LOCK_RATIO 10

struct thread_params {
 int i;
 pthread_t t;
 RWLock *rwl;
 pthread_barrier_t *brr;
};

void* thread_run(void *pv) {
 thread_params *tp = (thread_params*) pv;
 if(tp != NULL) {
  if(tp->i % READ_WRITE_LOCK_RATIO > 0) {
   /*
    * Let's stampede shared/reader's lock to see whether 
    * we will have any issues
    */
   pthread_barrier_wait(tp->brr);
   assert(tp->rwl->RDLock() == 0);
   cout << "Reader's thread: " << tp->i << " (tid: " << pthread_self() << " is now unblocked and is about to unlock" << endl;
  } else {
   assert(tp->rwl->WRLock() == 0);
   sleep(1);
   cout << "Writer's thread: " << tp->i << " (tid: " << pthread_self() << ") is about to unlock" << endl;
  }
  assert(tp->rwl->RWUnlock() == 0);
 }
 return NULL;
}

int main() {
 RWLock rwl;
 pthread_barrier_t brr; 
 thread_params tpa[NUMBER_OF_THREADS];
 assert(pthread_barrier_init(&brr, NULL,  (sizeof(tpa) / sizeof(tpa[0])) - (NUMBER_OF_THREADS / READ_WRITE_LOCK_RATIO)) == 0);
 int i(0);
 for(;i < sizeof(tpa) / sizeof(tpa[0]); ++i) {
  tpa[i].i = i;
  tpa[i].rwl = &rwl;
  tpa[i].brr = &brr;
  pthread_create(&(tpa[i].t), NULL, &thread_run, (void *)&tpa[i]);
 }
 for(i = 0;i < sizeof(tpa) / sizeof(tpa[0]); ++i) {
  pthread_join(tpa[i].t, NULL);
 }
 pthread_barrier_destroy(&brr);
 return 0;
}
