#include <iostream>
#include <typeinfo>
using namespace std;

/*
Q: where rtti is stored?
A: vtable contains pointer to type_info structure.
N: problem: if class is not a part of derivation hierarchy typeid() still works!
*/

class B {
public:
 virtual const char* f() { return "B::f"; }
};

class D : public B {
public:
 const char* f() { return "D::f"; }
};

class C {};

int main() {
 B b, *pb = &b;
 D d;
 C c;
 cout << typeid(b).name() << ": " << b.f() << endl;
 cout << typeid(pb).name() << ": " << pb->f() << endl;
#if 1
 pb = &d;
#else
 pb = new D;
#endif
 cout << typeid(pb).name() << ": " << pb->f() << endl;
 cout << typeid(*pb).name() << ": " << (*pb).f() << endl;
 cout << typeid(d).name() << ": " << d.f() << endl;
 cout << "typeid(c).name(): " << typeid(c).name() 
  << ", typeid(&c).name(): " << typeid(&c).name()
  << ", sizeof(c) = " << sizeof(c) << endl;
}
