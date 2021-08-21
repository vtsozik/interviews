#include <iostream>
using namespace std;

struct A {
 int i;
 A(int i) : i(i) {
  cout << "Constructing A from i = " << i << '\n';
 }
};

#ifndef SHOULD_NOT_COMPILE_BUT_DOES
void f(const A& a) {
 cout << "Inside 'void f(const A& a)', with a.i = " << a.i << '\n';
}
#else
void f(const A& a, const A& b) {
 cout << "Inside 'void f(const A& a, const A& b)'" << '\n';
}

void f(int i1, int i2) {
 cout << "Inside 'void f(int i1, int i2)'" << '\n';
}
#endif

int main() {
 int i = 7;
#ifndef SHOULD_NOT_COMPILE_BUT_DOES
 cout << "Calling 'f(i)'" << '\n';
 f(i);
#else
 cout << "Calling 'f(i, i)'" << '\n';
 f(i, i);
 A a(i);
 cout << "Calling 'f(i, a)'" << '\n';
 f(i, a);
 cout << "Calling 'f(a, i)'" << '\n';
 f(a, i);
 cout << "Calling 'f(a, a)'" << '\n';
 f(a, a);
#endif
 return 0;
}
