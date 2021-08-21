/*
Q: Will compiler provide a default constructor if
developer provides parametrized constructor?
A:
*/

#include <iostream>
using namespace std;

class A {
 int i;
 static int j;
public:
#if 1
 A(const int i) : i(i) {}
#endif
 void printI() {
  int k;
  static int l;
  cout << i << ' ' << j << ' ' << k << ' ' << l << endl;
 }
};

int A::j;

int main() {
#if 0
 A a(7);
 a.printI();
#else
 A a0;
 a0.printI();
#endif
}
