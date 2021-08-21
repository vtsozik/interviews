/*
 * NOTES.
 *
 * This program implements simple memory heap management via simple_malloc and simple_free functions
 * Global variables are protected by a single mutex lock that does create a lot of contention. Heap
 * address space is contigious and hence slicing and stitching algorithms are implemented to limit
 * heap defragmentation. More elaborate implementation can use mmap instead of sbrk system call to
 * extend heap space. Eventhough mmap will create non-contigious heap space slicing and stitching 
 * algorithms can be modified to check heap_segment_address+heap_segment_size!=next_heap_segment_address
 * condition to detect discontinuity in heap address space. Alternatively to slicing and stiching
 * algorithms non-contigious heap space can be represented as a balanced binary tree and sorted by
 * heap segment size. Best fit search algorithm will compare requested size distance from first 
 * (smallest) and last (largest) heap_segment to determine which end to choose as a starting point 
 * for iteration. This however will add additional running complexity as every new heap segment
 * inserted into heap space may cause tree rebalancing and relinking multiple next heap segment 
 * pointers. Another benefit of non-contigious heap space are  multiple arenas or heap allocation 
 * areas that can be accessed simultaneously by multiple threads to relieve the contention. Multiple
 * threads can be "beaned" by pthread_self() % NUMBER_OF_ARENAS to different arenas. Each arena will
 * use unique lock to ensure atomicity where required and hence greatly reduce contention. I think
 * the latest glibc malloc/free implementation uses mmap with non-contigious size ordered heap space 
 * divided to multiple arenas if application is compiled with -lpthread.
 * 
 * The program runs my implementation (benchmode = 0) against standard malloc/free glibc implementation 
 * (benchmode = 1) and lists total nanosecond timings for 220 threads. I listed sample program output
 * below:
 *
 * [vtsozik@SR71 quartz]$ ./a.out 
 * benchmode = 0, total_time = 3571118135, total_alloc_time = 3438064267, total_free_time = 133053868
 * benchmode = 1, total_time = 4207306108, total_alloc_time = 4182239137, total_free_time = 25066971
 * [vtsozik@SR71 quartz]$ 
 *
 * Nevertheless it's not a fair comparison as mmap intializes memory to 0s and sbreak doesn't. 
 * I also limited allocation size to the following range sizeof(long) * [1, 0xffff]
 * Test harness threads allocate memory chunks of random size, check access and corruption, collect 
 * and print nanosecond timings of malloc/free executions. Program compiled with:
 *
 * g++ -O3 simple_malloc.cpp -lpthread -fstrict-overflow -fsanitize=signed-integer-overflow
 *
 * Vadim Tsozik, 02/28/2016
 */

#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/mman.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

/*
 * Here I use static keyword as private access specifier. If these routines 
 * compiled into linkable object static variables will be only seen in this
 * compilation unit and hence will be private for client code
 */
static void *heap_start = NULL;
static size_t heap_size = 0;
static pthread_mutex_t lck = PTHREAD_MUTEX_INITIALIZER;
static struct heap_seg { heap_seg *next; size_t size; size_t free; } *last_seg = NULL;

static void* find_free_seg(const size_t s) {
 if(s < heap_size) {
  heap_seg *it = (heap_seg *) heap_start;
  do {
   /* 
    * For simplicity I use "first-to-fit" search model to find free segment.
    * If larger than requested free segment is sliced into two segments,
    * with second segment matching the requested size
    */
   if(it->free >= s) {
    it->free -= s;
    it->size = it->free;
    void *c = ((void *)it) + it->size;
    heap_seg *hs = (heap_seg *) c;
    hs->next = it->next;
    it->next = hs;
    if(last_seg == it) {
     last_seg = hs; 
    }
    return c;
   }
   it = it->next;
  } while(it != NULL);
 }
 return NULL;
}

void *simple_malloc(size_t s) {
 if(s <= 0) {
  return NULL;
 }
 pthread_mutex_lock(&lck);
 if(heap_start == NULL) {
  heap_start= sbrk(0);
 }
 s += sizeof(heap_seg);
 void *c = find_free_seg(s);
 heap_seg *hs = (heap_seg *) c;
 if(c == NULL) {
  /* mmap is slow since unitialized doesn't work in glibc implementation I have. 
   * Moreover since MAP_FIXED doesn't work either, allocations are not contigious
   * so slicing and stiching has to compare size and next to see whether next node 
   * is contiguous and perform slicing and stiching on contigious chunks only
   */
#ifdef USE_MMAP_NON_CONTIGUOUS
  c = mmap(heap_start + heap_size, s, PROT_READ | PROT_WRITE, MAP_PRIVATE | /* MAP_FIXED | MAP_UNINITIALIZED |*/ MAP_ANONYMOUS, -1, 0);
#else
  c = sbrk(s); 
#endif
  if(c == (void *) -1) {
   pthread_mutex_unlock(&lck);
   return NULL;
  }
  /*
   * Asserting address space to be contiguous
   */
  if(c != heap_start + heap_size) {
   pthread_mutex_unlock(&lck);
   assert(c == heap_start + heap_size); 
  }
  heap_size += s;
  hs = (heap_seg *) c; 
  hs->next = NULL;
  if(last_seg != NULL) {
   last_seg->next = hs;
  }
  last_seg = hs;
 }
 hs->size = s;
 hs->free = 0;
 pthread_mutex_unlock(&lck);
 return c + sizeof(heap_seg);
}

void simple_free(void *c) {
 pthread_mutex_lock(&lck);
 heap_seg *hs = (heap_seg *) (c - sizeof(heap_seg));
 hs->free = hs->size;
/*
 * Stitch freed segment with next free segment.
 * This is only possible with contigious address space
 */
 if(hs->next != NULL && hs->next->free == hs->next->size) {
  hs->free += hs->next->free;
  hs->size = hs->free;
  if(last_seg == hs->next) {
   hs->next = NULL;
   last_seg = hs;
  } else {
   hs->next = hs->next->next;
  }
 }
 pthread_mutex_unlock(&lck);
}

/*
 * Test harness
 */

#include <string.h>
#include <time.h>
#include <stdio.h>
#define MAX(v1, v2) ((v1 > v2) ? v1 : v2)

static unsigned benchmode = 0;
static long total_alloc_time = 0, total_free_time = 0; 
static pthread_mutex_t thlck = PTHREAD_MUTEX_INITIALIZER;

long simple_cksum(long *p, size_t s) {
 long c = p[0];
 for(int i = 1; i < s; ++i) {
  c = c ^ p[i];
 }
 return c;
}

void* thread_driver(void *attr) {
/*
 * Although rand() is non-reentrant or thread safe it's acceptable
 * to tradeof some enthropy reduction due to the same random numbers used
 * in several threads rather than mutex it or maintain its unique state
 * per thread for this particular application
 */
 size_t s = MAX(rand(), 1) % 0xffff, sa = s * sizeof(long); 
 struct timespec tp_start, tp_end;;
 clock_gettime(CLOCK_REALTIME, &tp_start);
 long *p = (long *) ((benchmode == 0) ? simple_malloc(sa) : malloc(sa));
 clock_gettime(CLOCK_REALTIME, &tp_end);
 pthread_mutex_lock(&thlck);
 total_alloc_time +=  tp_end.tv_nsec - tp_start.tv_nsec;
 pthread_mutex_unlock(&thlck);
 assert(p != NULL);
 for(int i = 0; i < s; ++i) {
  p[i] = rand(); 
 }
 long c = simple_cksum(p, s); 
 double mil = 1e6;
 usleep(RAND_MAX < mil ? mil / RAND_MAX * rand() : rand() % (int) mil);
 assert(c == simple_cksum(p, s)); 
 clock_gettime(CLOCK_REALTIME, &tp_start);
 if(benchmode == 0) {
  simple_free(p);
 } else {
  free(p);
 }
 clock_gettime(CLOCK_REALTIME, &tp_end);
 pthread_mutex_lock(&thlck);
 total_free_time +=  tp_end.tv_nsec - tp_start.tv_nsec;
 pthread_mutex_unlock(&thlck);
 return NULL;
}

int main() {
 const int nthrds = 220;
 pthread_t thrds[nthrds]; 
 srand(time(NULL));
 for(;benchmode < 2; ++benchmode) {
  int i;
  for(i = 0; i < nthrds; ++i) {
   pthread_create(&thrds[i], NULL, thread_driver, NULL);
  }
  for(i = 0; i < nthrds; ++i) {
   pthread_join(thrds[i], NULL);
  }
  printf("benchmode = %u, total_time = %u, total_alloc_time = %u, total_free_time = %u\n", benchmode, total_alloc_time + total_free_time, total_alloc_time, total_free_time);
  total_alloc_time = total_free_time = 0;
 }
 return 0;
}
