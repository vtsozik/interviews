/*
 * Dear Andreas,
 *
 * During the interview you posed an open problem about tree recursion and rather severe limits imposed 
 * by low amount of memory allocated for stack segment (when compared to the heap segment size). I believe I 
 * mentioned that any form of stack recursion can be replaced with "tail" recursion or iterative approach
 * where pointer to the node is assigned to the value of next or previous node pointer. Moreover if node has a 
 * pointer to the previous node then "tail" recursion can be implemented without additional memory complexity 
 * or "in-place".
 * This question really sparked my interest and made to investigate the problem a bit further. For starters
 * I wrote a simple program that contains a single function which recurses itself to the point of failure. 
 * Everytime it enters new stack it prints and then increments value of single long parameter passed to the 
 * recursion frame. It also prints the number of stack memory segment bytes consumed by recursion so far:
 *
 * void print(long a) {
 *  printf("%u, %u\n", a, (sizeof(a) * a));
 *  print(++a);
 * }
 *
 * Interesting to see that with 8MB of available stack space it takes only ~2MB of usable memory allocated
 * for stack variables to exhaust the entire stack segment:
 *
 * [vtsozik@SR71 mongodb]$ ./a.out
 * ...
 * 261846, 2094768
 * Segmentation fault (core dumped)
 * [vtsozik@SR71 mongodb]$ ulimit -s
 * 8192
 * [vtsozik@SR71 mongodb]$
 *
 * I also read (unfortunately don't remember where) that any recursive solution will be slower than analogous 
 * iterative approach due to the large overhead imposed by hidden code that manages stack frames. To verify this 
 * I wrote a small demostration program below. This program recursively generates perfectly balanced and ordered 
 * binary tree and then scans it recursively and iteratively printing scanned node values in the same order for 
 * both recursive and iterative algorithms. While running each algorithm cumulative time required to traverse the 
 * entire binary tree data structure is measured and printed. Due to the blocking nature of i/o calls is time 
 * spent on them is discarded to keep overall run time variation to the minimum.
 *
 * Looking at RecursiveScan (5 lines, 3 calls, one of them recursive) and IterativeScan (21 lines, 2 calls,
 * no recursion) function below one may assume that RecursiveScan will take less time to execute on the same tree
 * depth as it has less lines of code to execute per each scanned node. But compiling this code with:
 *
 * [vtsozik@SR71 mongodb]$ g++ -O0 bintreerecursionvsiteration.cpp
 *
 * and then running it with:
 *
 * [vtsozik@SR71 mongodb]$ ./a.out
 *
 * will yield unexpected results:
 *
 * Recursive Scan:
 * Value: 1, Node: 0x6e10a0, Parent: 0x6e1070, Left: 0, Right: 0
 * Value: 2, Node: 0x6e1070, Parent: 0x6e1040, Left: 0x6e10a0, Right: 0x6e10d0
 * Value: 3, Node: 0x6e10d0, Parent: 0x6e1070, Left: 0, Right: 0
 * Value: 4, Node: 0x6e1040, Parent: 0x6e1010, Left: 0x6e1070, Right: 0x6e1100
 * Value: 5, Node: 0x6e1130, Parent: 0x6e1100, Left: 0, Right: 0
 * Value: 6, Node: 0x6e1100, Parent: 0x6e1040, Left: 0x6e1130, Right: 0x6e1160
 * Value: 7, Node: 0x6e1160, Parent: 0x6e1100, Left: 0, Right: 0
 * Value: 8, Node: 0x6e1010, Parent: 0, Left: 0x6e1040, Right: 0x6e1190
 * Value: 9, Node: 0x6e11f0, Parent: 0x6e11c0, Left: 0, Right: 0
 * Value: 10, Node: 0x6e11c0, Parent: 0x6e1190, Left: 0x6e11f0, Right: 0x6e1220
 * Value: 11, Node: 0x6e1220, Parent: 0x6e11c0, Left: 0, Right: 0
 * Value: 12, Node: 0x6e1190, Parent: 0x6e1010, Left: 0x6e11c0, Right: 0x6e1250
 * Value: 13, Node: 0x6e1280, Parent: 0x6e1250, Left: 0, Right: 0
 * Value: 14, Node: 0x6e1250, Parent: 0x6e1190, Left: 0x6e1280, Right: 0x6e12b0
 * Value: 15, Node: 0x6e12b0, Parent: 0x6e1250, Left: 0, Right: 0
 * Recursive Scan, took 8803 nanoseconds excluding I/O
 * Iterative Scan:
 * Value: 1, Node: 0x6e10a0, Parent: 0x6e1070, Left: 0, Right: 0
 * Value: 2, Node: 0x6e1070, Parent: 0x6e1040, Left: 0x6e10a0, Right: 0x6e10d0
 * Value: 3, Node: 0x6e10d0, Parent: 0x6e1070, Left: 0, Right: 0
 * Value: 4, Node: 0x6e1040, Parent: 0x6e1010, Left: 0x6e1070, Right: 0x6e1100
 * Value: 5, Node: 0x6e1130, Parent: 0x6e1100, Left: 0, Right: 0
 * Value: 6, Node: 0x6e1100, Parent: 0x6e1040, Left: 0x6e1130, Right: 0x6e1160
 * Value: 7, Node: 0x6e1160, Parent: 0x6e1100, Left: 0, Right: 0
 * Value: 8, Node: 0x6e1010, Parent: 0, Left: 0x6e1040, Right: 0x6e1190
 * Value: 9, Node: 0x6e11f0, Parent: 0x6e11c0, Left: 0, Right: 0
 * Value: 10, Node: 0x6e11c0, Parent: 0x6e1190, Left: 0x6e11f0, Right: 0x6e1220
 * Value: 11, Node: 0x6e1220, Parent: 0x6e11c0, Left: 0, Right: 0
 * Value: 12, Node: 0x6e1190, Parent: 0x6e1010, Left: 0x6e11c0, Right: 0x6e1250
 * Value: 13, Node: 0x6e1280, Parent: 0x6e1250, Left: 0, Right: 0
 * Value: 14, Node: 0x6e1250, Parent: 0x6e1190, Left: 0x6e1280, Right: 0x6e12b0
 * Value: 15, Node: 0x6e12b0, Parent: 0x6e1250, Left: 0, Right: 0
 * Iterative Scan, took 6414 nanoseconds excluding I/O
 *
 * Although in the example above I disabled compiler optimizations to avoid inlining 
 * of recursive function or unrolling loop in the iterative function, if you compile it 
 * with (stage 3 optimizations):
 *
 * [vtsozik@SR71 mongodb]$ g++ -O3 bintreerecursionvsiteration.cpp
 *
 * the produced result will still show that iterative approach is faster, but run time
 * differences will be less pronounced.
 *
 * In addition working on large data structures will make iterative approach mandatory
 * as recursion will quickly render itself unfeasable with growing tree depth. This 
 * also hints on why ordered STL containers are using iterative approach for traversing
 * the binary trees or their re-balancing. Even at the expense of adding pointer to 
 * the parental node iterative solution may be more optimal as tree depth cannot be 
 * anticipated. 
 *
 * Thank you in advance for your consideration,
 *  Vadim Tsozik.
 *
 */

#include <iostream>
#include <math.h>
using namespace std;

struct Node {

 int value;
 Node *left;
 Node *right;
 Node *parent;

 Node(const int &vl, Node *prnt = NULL) : value(vl), parent(prnt), left(NULL), right(NULL) {}

 ~Node() {
  if(left != NULL) {
   delete left; 
  }
  if(right != NULL) {
   delete right; 
  }
 }

 void PrintNode() {
  cout << "Value: " << value << ", Node: " << this << ", Parent: " << parent << ", Left: " << left << ", Right: " << right << endl;
 }

};

class BinTree {

 Node *m_pnRoot;
 long m_lNTS;
 /*
 * Declared as member variables to avoid recursive stack size increase
 */
 struct timespec m_tsStart, m_tsEnd;

 void GenerateBalancedTree(Node *parent, int level) {
  if(--level >= 0) {
   int step = static_cast<int>(pow(2, level));
   GenerateBalancedTree(parent->left = new Node(parent->value - step, parent), level);
   GenerateBalancedTree(parent->right = new Node(parent->value + step, parent), level);
  }
 }

 typedef void (BinTree::*FP)(Node *node);

 void RunBenchmark(const string &bn, FP fp) {
  m_lNTS = 0;
  cout << bn << ':' << endl;
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &m_tsStart);
  (this->*fp)(GetRoot());
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &m_tsEnd);
  m_lNTS += (m_tsEnd.tv_nsec - m_tsStart.tv_nsec);
  cout << bn << ", took " << m_lNTS << " nanoseconds excluding I/O" << endl;
 }

 public:

 BinTree() : m_pnRoot(NULL) {}

 ~BinTree() {
  if(m_pnRoot != NULL) {
   delete m_pnRoot;
  }
 }

 Node *GetRoot() { return m_pnRoot; }

 void PrintNode(Node *p) {
  /*
  * I exclude i/o timing as it entails a blocking system call
  */
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &m_tsEnd);
  p->PrintNode();
  m_lNTS += (m_tsEnd.tv_nsec - m_tsStart.tv_nsec);
  clock_gettime(CLOCK_THREAD_CPUTIME_ID, &m_tsStart);
 }

 void GenerateBalancedTree(int depth) {
  GenerateBalancedTree(m_pnRoot = new Node(static_cast<int>(pow(2, --depth))), depth);
 }

 void RecursiveScan(Node *node) {
  if(node != NULL) {
   RecursiveScan(node->left);
   PrintNode(node);
   RecursiveScan(node->right);
  }
 }

 void IterativeScan(Node *node) {
  Node *current = node;
  if(current != NULL) {
   do {
    if(current->parent == NULL || current->parent->right == current) {
     while(current->left != NULL) {
      current = current->left;
     }
     PrintNode(current);
    }
    if(current->parent != NULL) {
     if(current->parent->left == current) {
      PrintNode(current->parent);
      current = current->parent->right;
     } else if(current->parent->right == current) {
      while(current->parent != NULL && current->parent->right == current) {
       current = current->parent;
      }
     }
    } 
   } while(current->parent != NULL);
  }
 }

 void BenchMarkScansWithoutIO() {
  RunBenchmark("Recursive Scan", &BinTree::RecursiveScan);
  RunBenchmark("Iterative Scan", &BinTree::IterativeScan);
 }

};

#define TREE_DEPTH 4

int main() {
 BinTree bt;
 bt.GenerateBalancedTree(TREE_DEPTH);
 bt.BenchMarkScansWithoutIO(); 
 return 0;
}
