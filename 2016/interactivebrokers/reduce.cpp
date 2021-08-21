#include <iostream>
#include <list>
using namespace std;

class NotEnoughElements {};

template <typename Container, typename Function>
typename Container::value_type
Reduce(const Container& c, Function fn) throw (NotEnoughElements) {
 typename Container::const_iterator it = c.begin();
 if(it == c.end()) {
  throw new NotEnoughElements;
 }
 typename Container::value_type sum = *it;
 while(++it != c.end()) {
	sum = fn(sum, *it);
 }
 return sum;
}

int main() {
 list<int> l;
 for(int i(1); i <= 5; ++i) {
  l.push_back(i);         
 }
 cout << Reduce(l, plus<int>()) << endl; 
return 0;
}
