#include <iostream>
using namespace std;

struct node {
 node(int i) : next(NULL), v(i) {}
 node *next;
 int v;
};

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

#ifdef NONRECURSIVELY
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
#else
node *reverse(node *h) {
 node *next, *current = h;
 while(h != NULL && h->next != NULL) {
  next = h->next;
  h->next = next->next;
  next->next = current;
  current = next;
 }
 return current;
}
void reverse(node **h) {
 *h = reverse(*h);
}
#endif

void deallocate(node *h) {
 node *t;
 while(h != NULL) {
  t = h;
  h = h->next; 
  delete t;
 }
}

int main() {
 node *h = allocate(10);
 print(h);
 reverse(&h);
 print(h);
 deallocate(h);
 return 0;
}
