#include <iostream>
#include <queue>
#include <stack>
using namespace std;

struct Node {

 int value;
 Node *left;
 Node *right;

 Node(const int &vl) : value(vl), left(NULL), right(NULL) {}

 ~Node() {
  if(left != NULL) {
   delete left; 
  }
  if(right != NULL) {
   delete right; 
  }
 }

 void PrintNode() {
  cout << "Value: " << value << ", Node: " << this << ", Left: " << left << ", Right: " << right << endl;
 }

};

class BinTree {

 Node *m_pnRoot;

 public:

 BinTree() : m_pnRoot(NULL) {}

 ~BinTree() {
  if(m_pnRoot != NULL) {
   delete m_pnRoot;
  }
 }

 void GenerateBalancedTree(int num_of_elems) {
  int i(0);
  queue<Node *> q;
  m_pnRoot = new Node(i++);
  q.push(m_pnRoot);
  while(i < num_of_elems) {
   Node *n = q.front();
   q.pop();
   if(i < num_of_elems) {
    n->left = new Node(i++);
    q.push(n->left);
   }
   if(i < num_of_elems) {
    n->right = new Node(i++);
    q.push(n->right);
   }
  }
 }

 void PrintBFS() {
  queue<Node *> q;
  q.push(m_pnRoot);
  while(!q.empty()) {
   Node *n = q.front();
   q.pop();
   if(n != NULL) {
    n->PrintNode();
    q.push(n->left);
    q.push(n->right);
   }
  }
 }

 void PrintDFS() {
  stack<Node *> s;
  s.push(m_pnRoot);
  while(!s.empty()) {
   Node *n = s.top();
   s.pop();
   if(n != NULL) {
    if(n->right != NULL) {
     s.push(n->right);
    }
    if(n->left != NULL) {
     s.push(n->left);
    }
    n->PrintNode();
   }
  }
 }
};

int main() {
 BinTree bt;
 bt.GenerateBalancedTree(7);
 cout << "BFS:" << endl;
 bt.PrintBFS();
 cout << "DFS:" << endl;
 bt.PrintDFS();
 return 0;
}
