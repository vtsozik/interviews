#include <iostream>
using namespace std;

class B {
public:
  virtual void f() { cout << "B::f()" << endl; }
};

class D : public B {
private:
  void f() { cout << "D::f()" << endl; }
};

int main() {
  D dobj;
  B* bptr = &dobj;
  D* dptr = &dobj;

  // valid, virtual B::f() is public,
  // D::f() is called
  bptr->f();

  // valid, virtual B::f() is public,
  // D::f() is called
  bptr = new D;
  bptr->f();

  // error, D::f() is private
  //dptr->f();
}
