#include <iostream>
using namespace std;

struct node {
 node *l,*r;
};

// depth-first recursive
int treeheight(node *n)  {
 if(n == NULL) 
  return 0;
 int l = 1 + treeheight(n->l),
  r = 1 + treeheight(n->r);
 return (l > r) ? l : r;
}

// breadth-first non-recursive
int treeheightnonrecursive(node *r) {
 node **a, **na;
 int i, h(1), n(1), nn(2 * n), c;
 if(r == NULL) {
  return 0;
 }
 a = new node*[n];
 a[0] = r;
 for(;;) {
  na = new node*[nn];
  for(i = 0, c = 0; i < n && a[i] != NULL; ++i) {
   if(a[i]->l != NULL) {
     na[c++] = a[i]->l;
   }
   if(a[i]->r != NULL) {
     na[c++] = a[i]->r;
   }
  }
  na[c] = NULL;
  delete[] a;
  a = na; 
  if(c > 0) {
   n = nn;
   nn = 2 * n;
   ++h;
  } else {
   break;
  }
 }
 delete[] a;
 return h;
}

void createbalancedtree(node **n, int h) {
 if((h--) > 0) { 
  *n = new node;
  createbalancedtree(&((*n)->l), h);
  createbalancedtree(&((*n)->r), h);
 } else {
  *n = NULL;
 }
}

int main() {
 int h(4);
 node *n;
 createbalancedtree(&n, h);
 cout << "Created balanced tree with height (dfs): " << treeheight(n) << endl;
 cout << "Created balanced tree with height (bfs): " << treeheightnonrecursive(n) << endl;
 return 0;
} 
