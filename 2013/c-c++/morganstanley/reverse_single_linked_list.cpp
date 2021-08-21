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

node *reverse(node *h) {
 node *t1, *t2 = h;
 while(h != NULL && h->next != NULL) {
  t1 = h->next;
  h->next = t1->next;
  t1->next = t2;
  t2 = t1;
 }
 return t2;
}

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
 h = reverse(h);
 print(h);
 deallocate(h);
 return 0;
}
