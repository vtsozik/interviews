#define DO_BOOST
#ifdef DO_BOOST
#include <boost/container/vector.hpp>
using namespace boost::container;
#else
#include <vector>
using namespace std;
#endif
#include <iostream>

int main() {
 vector<int> v;
 for(int i(0); i < 130; ++i) {
  std::cout << "Capacity before adding " << i << " element: " << v.capacity() << std::endl;
  v.push_back(i);
 }
 return 0;
}
