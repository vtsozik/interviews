#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

class A {
 public:
  int a;
  double b;
  bool c;
  int *d; 
  char e[7];
#if 0
 A() {
  memset(this, 0, sizeof(*this));
 }
#endif
};

int main() {
 A a;
 cout << "int: " << a.a << " double: " << a.b << " bool: "  << a.c << " pointer: " << a.d << " char string: " << a.e << " was double initialized with NaN: " << (isnan(a.b) ? "true" : "false") << endl;
 return 0;
}
