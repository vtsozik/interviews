#include <iostream>
using namespace std;

struct node {
 int v;
 node *n; 
 node(int i) : v(i), n(NULL) {}
};

void printlist(node *h) {
 for(int i = 1; h != NULL; h = h->n, ++i) {
  cout << "Element #" << i << ", Value: " << h->v << endl;
 }
}

void deleteSingleLinkedListElement(node *d) {
 if(d != NULL) {
  node *n = d->n;
  if(n != NULL) {
   d->v = n->v;
   d->n = n->n;
   delete n;
  } else {
   /*
    If list element to delete is the last one,
    we will end up with non-NULL terminated list.
   */
   delete d;
  }

 }
}

int main() {
 int n = 10, m = 5;
 node *h(new node(1)), *p(h), *d;
 for(int i = 2; i <= n; ++i) {
  p->n = new node(i);
  p = p->n;
  if(i == m) {
   d = p;
  }
 }
 cout << "Before deletion of element #" << m << endl;
 printlist(h);
 deleteSingleLinkedListElement(d);
 cout << "After deletion of element #" << m << endl;
 printlist(h);
 p = h;
 while(p != NULL) {
  d = p;
  p = p->n;
  delete d;
 }
 return 0;
}
