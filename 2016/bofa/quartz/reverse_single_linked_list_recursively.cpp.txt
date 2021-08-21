/*
 * NOTES.
 *
 * This is simple implementation of single linked list reverse algorithm
 * in recursive manner. Reverse also happens in place and has linear complexity
 * Interesting that if compared to non-recursive implementation this implementation 
 * will require one less variable to be allocated on a stack of reverse function.
 *
 * It was compiled with:
 *
 * [vtsozik@SR71 quartz]$ g++ reverse_single_linked_list_recursively.cpp 
 *
 * And produced the following output:
 *
 * [vtsozik@SR71 quartz]$ ./a.out 
 * 1 2 3 4 5 6 7 8 9 10
 * 10 9 8 7 6 5 4 3 2 1
 * [vtsozik@SR71 quartz]$
 * 
 * Vadim Tsozik, 02/28/2016
 */

#include <iostream>
using namespace std;

struct node {
 node(int i) : next(NULL), v(i) {}
 node *next;
 int v;
};

/*
 * Some infrastructure code to facilitate testing
 */

void print(node *h) {
 while(h != NULL) {
  cout << ' ' << h->v;
  h = h->next;
 }
 cout << endl;
}

node *allocate(int n) {
 node *h = NULL;
 for(int i = n; i > 0; --i) {
  if(h == NULL) {
   h = new node(i);
  } else {
   node *t = new node(i);
   t->next = h;
   h = t;
  }
 }
 return h;
}

void deallocate(node *h) {
 node *t;
 while(h != NULL) {
  t = h;
  h = h->next; 
  delete t;
 }
}

/*
 * End of infrastructure code
 */

/*
 * Here pointer-to-pointer to node is used 
 * to correct head node pointer value at the
 * exit from reverse recursive function
 */ 
void reverse(node **h) {
 if(*h == NULL || (*h)->next == NULL) {
  return;
 } else {
  node *next = (*h)->next;
  reverse(&next);
  (*h)->next->next = *h;
  (*h)->next = NULL;
  (*h) = next;
 }
}

/*
 * Simple test harness
 */
int main() {
 node *h = allocate(10);
 print(h);
 reverse(&h);
 print(h);
 deallocate(h);
 return 0;
}
