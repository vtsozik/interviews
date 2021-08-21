#include <iostream>
#include <list>
#include <unordered_set>

using namespace std;

void printList(const list<int> &l) {
 cout << "list (size=" << l.size() << "):";
 for(list<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
  cout << ' ' << *it;
 }
 cout << endl;
}

void removeDuplicates(list<int> &l) {
 std::unordered_set<int> us;
 list<int>::iterator tmp = l.begin();
 us.insert(*tmp);
 for(list<int>::iterator it = ++tmp; it != l.end();) {
  ++tmp;
  if(!us.insert(*it).second) {
   l.erase(it);
  }
  it = tmp;
 }
}

int main() {
 //using c++11 list initialization
 list<int> l = {5, 1, 1, 2, 2, 2, 4, 3};
 cout << "Before: ";
 printList(l);
 removeDuplicates(l); 
 cout << "After: ";
 printList(l);
 return 0;
}
