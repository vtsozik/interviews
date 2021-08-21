#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <ucontext.h>
#include <iostream>
using namespace std;

#define QUANT 1
#define STACK_SIZE 65536
ucontext_t threads[2];
int currthread(-1), numofthreads(0);
int csc(0);

void thread(char *tn, int *tc) {
 while(true) {
  cout << "In thread " << *tn << ' ' << ++(*tc) << endl;
 }
}

typedef void (*shfp)(int);
typedef void (*tfp)(void);

void yield() {
 int oldthread = currthread;
 currthread = (oldthread + 1) % (sizeof(threads) / sizeof(threads[0]));
 if(oldthread < 0) {
  setcontext(&threads[currthread]);
 } else {
  swapcontext(&threads[oldthread], &threads[currthread]);
 }
}

void signal_handler(int sig) {
 if(sig == SIGVTALRM) {
  cout << "Context switch #" << ++csc << " ..." << endl;
  yield();
 } 
}

void setimer(int ms) {
  struct itimerval it_val_new;
  it_val_new.it_value.tv_sec = ms / 1000;
  it_val_new.it_value.tv_usec = (ms * 1000) % 1000000;
  it_val_new.it_interval.tv_sec = it_val_new.it_value.tv_sec;
  it_val_new.it_interval.tv_usec = it_val_new.it_value.tv_usec;
  if(setitimer(ITIMER_VIRTUAL, &it_val_new, NULL) == -1) {
   perror("error calling setitimer()");
   exit(1);
  }
}

void addathread(tfp p, char tn, int tc) {
  ucontext_t *uc = &threads[numofthreads];
  getcontext(uc);
  uc->uc_link = NULL;
  uc->uc_stack.ss_sp = malloc(STACK_SIZE);
  uc->uc_stack.ss_size = STACK_SIZE;
  uc->uc_stack.ss_flags = 0;
  char *ptn = (char *)malloc(sizeof(char));
  *ptn = tn;
  int *ptc = (int *)malloc(sizeof(int));
  *ptc = tc;
  makecontext(uc, p, 2, (void*)ptn, (void*)ptc);
  ++numofthreads;
}

void init() {
 if(signal(SIGVTALRM, signal_handler) == (shfp) -1) {
   perror("unable to set signal_handler()");
   exit(1);
  }
  addathread((tfp)thread, 'A', 0);
  addathread((tfp)thread, 'B', 0);
  setimer(QUANT);
}

int main() {
 setbuf(stdout, NULL);
 init();
 raise(SIGVTALRM);
 return 0;
}
