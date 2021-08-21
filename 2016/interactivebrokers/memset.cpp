#include <string.h>
#include <iostream>
using namespace std;

class A {
 public:
 float f;
 int i;
 A() { 
   i = 7;
   f = -6.6;
 }
 void memsetme() {
   memset(this, 0, sizeof(*this)); 
 }
};

int main() {
 A a;
 cout << a.f << ' ' << a.i << endl;
 a.memsetme();
 cout << a.f << ' ' << a.i << endl;
 return 0;
}
