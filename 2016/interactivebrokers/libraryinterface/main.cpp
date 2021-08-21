#include <iostream>
#include "lib.hpp"
using namespace std;

class B : public A {
public:
 B() : A() {
  cout << "B ctor" << endl;
 }
 ~B() { cout << "B dctor" << endl; }
};

int main() {
 A *a = new B();
 a->f();
 delete a;
 return 0;
}
