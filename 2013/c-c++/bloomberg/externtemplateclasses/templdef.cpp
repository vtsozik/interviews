#include "templdecl.h"

template <class T> int size(const T &t) {
 return sizeof(t);
}

#if 1
template int size<int>(const int &i);
#else
#include <iostream>
using namespace std;
int main() {
 cout << size(7) << endl;
}
#endif
