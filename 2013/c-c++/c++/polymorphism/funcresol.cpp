#include <iostream>
using namespace std;

class Base {
public:
 Base() { cout << "In Base ctor: " << this << endl; print(); }
 virtual void print() { cout << "In Base print " << this << endl; }
 void scopeResolution() { cout << "In scopeResolution: " << this << endl; print(); Base::print(); 
  //Derived::print(); // - Will not compile; 
 }
#if 1
 virtual ~Base() { cout << "In Base dtor:" << this << endl; print(); }
#else
 ~Base() { cout << "In Base dtor:" << this << endl; print(); }
#endif
};

class Derived : public Base {
public:
 Derived() { cout << "In Derived ctor: " << this << endl; print(); }
 void print() { cout << "In Derived print " << this << endl; }
 //int print() { cout << "In Derived print" << endl; } // - Nope, doesn't compile
 ~Derived() { cout << "In Derived dtor: " << this << endl; print(); }
};

int main() {
 Derived d;
 Base *bs = &d, *bh = new Derived();;
 cout << "Construction and initialization done!" << endl;
 bs->print();
 bs->scopeResolution();
 cout << "Begin deallocation" << endl;
 delete bh;
 return 0;
}
