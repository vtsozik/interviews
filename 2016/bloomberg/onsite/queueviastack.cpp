/*
 * Q: Implement queue using only stack datastructure.
 * A: Compile with: g++ -std=c++11 queueviastack.cpp
 */

#include <stack>
#include <iostream>
using namespace std;

template <class E> class queueviastack {
 stack<E> m_sIn, m_sOut;
 public:
 void enqueue(const E &e) {
  while(!m_sOut.empty()) {
   m_sIn.push(m_sOut.top());
   m_sOut.pop();
  } 
  m_sIn.push(e);
 }
 E&& dequeue() {
  while(!m_sIn.empty()) {
   m_sOut.push(m_sIn.top());
   m_sIn.pop();
  }
  E e(m_sOut.top());
  m_sOut.pop();
  return move(e);
 }
 bool empty() const {
  return (m_sIn.empty() && m_sOut.empty());
 }
};

int main() {
 queueviastack<int> q;
 for(int i(1); i <= 10; ++i) {
  q.enqueue(i);
 }
 while(!q.empty()) {
  cout << q.dequeue() << ' ';
 }
 cout << endl;
 return 0;
}
