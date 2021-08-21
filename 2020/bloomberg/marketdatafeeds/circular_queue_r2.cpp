#include <iostream>
#include <sstream>
#include <cassert>
using namespace std;

/*
 * Circular queuee - provide implementations for the functions below. 
 * Push should throw if number of elements reached is already equal
 * to initial capacity. New elements are pushed to fill slots that
 * were taken by elements that were popped. Don't use existing std
 * datastructures.
 */
template <class ElementT>
class CircularQueue
{
      template <class T> struct Node {
          T m_t;
	  Node<ElementT> *m_next;
	  Node(const T &t) : m_t(t), m_next(NULL) {}
      };
      Node<ElementT> *m_head, *m_tail;
      size_t m_capacity;
      size_t m_size;
      
      public:
      CircularQueue(size_t capacity) : m_head(NULL), m_capacity(capacity), m_size(0) {}   

      virtual ~CircularQueue() {
          free();
      }

      void free()
      {
          Node<ElementT> *p(m_head);
	  while (p) 
	  {
              Node<ElementT> *t(p);
	      p = p->m_next;
	      delete t;
	  }
	  m_head = m_tail = NULL;
      }

      void push(const ElementT& cref)
      {
          if (m_size == m_capacity)
          {
	      stringstream ss;
	      ss << "Overflow error: can't store more than " << m_capacity << " elements.";
              throw overflow_error(ss.str());
          } 
	  Node<ElementT> *n = new Node<ElementT>(cref);
	  if (m_head == NULL)
	  {
              m_head = m_tail = n;
	  }
	  else
	  {
	      m_tail->m_next = n;
	      m_tail = m_tail->m_next;
          }
	  ++m_size;
      }
      void pop()
      {
          if (m_head == NULL)
	  {
              throw underflow_error("Underflow error: can't pop an element from an empty queue.");
	  }
	  Node<ElementT> *t(m_head); 
	  if (m_head == m_tail)
	  {
	      m_head = m_tail = NULL;
	  }
	  else
	  {
	      m_head = m_head->m_next;
	  }
	  delete t;
          --m_size; 
      }
      bool empty()
      {
          return m_head == NULL;
      }
      const ElementT& front()
      {
	  if (m_head == NULL)
          {
              throw underflow_error("Underflow error: can't front an element from an empty queue.");
          }
          return m_head->m_t;
      }
      const ElementT& back()
      {
	  if (m_tail == NULL)
          {
              throw underflow_error("Underflow error: can't tail an element from an empty queue.");
          }
          return m_tail->m_t;
      }
};

int main() 
{
    int capacity(5), i(1);
    CircularQueue<int> cq(capacity);
    assert(cq.empty());
    for (; i <= capacity + 1; ++i)
    {
        try 
	{
            cq.push(i);
	}
	catch(const exception &e)
	{
            cout << e.what() << endl;
	    break;
	}
    }
    assert(cq.front() == 1);
    assert(cq.back() == 5);
    cq.pop();
    cq.pop();
    assert(cq.front() == 3);
    assert(cq.back() == 5);
    assert(i > 5);
    cq.push(i);
    assert(cq.front() == 3);
    assert(cq.back() == i);
    return 0;
}
