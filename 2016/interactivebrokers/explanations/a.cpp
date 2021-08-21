#include <iostream>
using namespace std;

class A {

public:

    virtual ~A() { cout << "A::~A" << endl; this->f(); }

    virtual void f() { cout << "A::f" << endl; }

    virtual void f1() { f(); }

};

class B: public A {

public:

    ~B() { cout << "B::~B" << endl; }

    virtual void f() { cout << "B::f" << endl; }

};

int main() {
A* a = new B;
a->f1();
delete a;
}
