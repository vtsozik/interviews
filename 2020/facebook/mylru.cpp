/*
 * Problem: Implement LRU key value cache
 * Solution: Use hashtable as main datastructure and
 * linked list to rank items for eviction priority
 */

#include <list>
#include <unordered_map>
#include <iostream>
#include <cassert>

using namespace std;

template <typename K, typename V> class mylru
{
 struct ValueWrapper
 {
  V m_v;
  typename list<K>::iterator m_iter;
 };
 const size_t m_fixedCapacity; 
 unordered_map<K, ValueWrapper> m_map;
 list<K> m_list; 
public:
 mylru(size_t capacity) : m_fixedCapacity(capacity), m_map(m_fixedCapacity) {}
 void add(const K &k, const V &v)
 {
  while (m_map.size() >= m_fixedCapacity)
  {
   m_map.erase(m_list.back());
   m_list.pop_back();
  } 
  ValueWrapper vw;
  vw.m_v = v;
  m_list.emplace_front(k);
  /* Can't really push new elements to the back as 
  * it is single linked list so only forward_iterator 
  * is allowed reverse_iterator or rbegin() is not available
  */
  vw.m_iter = m_list.begin(); 
  m_map.emplace(make_pair(k, vw));
 }

 bool get(const K &k, V &v)
 {
  typename unordered_map<K, ValueWrapper>::iterator iter(m_map.find(k));
  bool found(iter != m_map.end());
  if (found);
  {
   m_list.erase(iter->second.m_iter);
   m_list.emplace_front(k);
   iter->second.m_iter = m_list.begin();
   v = iter->second.m_v; 
  }
  return found;
 }

 inline const list<K>& getEvictionList() const { return m_list; }

 void dump() const
 {
  for (typename list<K>::const_iterator cli(m_list.begin()); 
   cli != m_list.end(); ++cli)
  {
   cout << '[' << *cli << ", " << m_map.find(*cli)->second.m_v << "] ";
  }
  if (m_list.empty())
  {
   cout << "[ , ]";
  }
  cout << endl;
 }
};

void unitTest()
{
 size_t cap(5), els(7);
 mylru<size_t, string> mc(cap);
 list<size_t> tl0{};
 assert(mc.getEvictionList() == tl0);
 cout << "Empty list:" << endl;
 mc.dump();

 cout << "Capacity: " << cap << ", elements: " << endl;
 for (size_t i(0); i < cap; ++i)
 {
  mc.add(i, to_string(i));
 }
 mc.dump();
 list<size_t> tl1{4, 3, 2, 1, 0};
 assert(mc.getEvictionList() == tl1);

 cout << "Adding " << els - cap << " over capacity:" << endl;
 for (size_t i(cap); i < els; ++i)
 {
  mc.add(i, to_string(i));
 }
 mc.dump();
 list<size_t> tl2{6, 5, 4, 3, 2};
 assert(mc.getEvictionList() == tl2);

 size_t m = ((els - cap) + (els - 1)) / 2;
 cout << "After accessing median element: " << m << ", eviction list:" << endl;
 string s;
 assert(mc.get(m, s));
 assert(m == stoul(s));
 mc.dump();
 list<size_t> tl3{4, 6, 5, 3, 2};
 assert(mc.getEvictionList() == tl3);
}

int main()
{
 unitTest();
 return 0;
}
