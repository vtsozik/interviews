#include <iostream>
using namespace std;

class A {/*virtual*/ int f(){}};
class B : public A {int i;};
class C : public A {int foo(){}};
class D {A a;};
class E {A a;int j;};

int main() {
 cout << "sizeof(A): " << sizeof(A) << endl; 
 cout << "sizeof(B): " << sizeof(B) << endl; 
 cout << "sizeof(C): " << sizeof(C) << endl; 
 cout << "sizeof(D): " << sizeof(D) << endl; 
 cout << "sizeof(E): " << sizeof(E) << endl; 
 return 0;
}
