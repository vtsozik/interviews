#include <iostream>
using namespace std;

int main() {
 int i(7), *pi(&i), ia, da;
 double d = 7e3, *pd(&d);
#if 1
 cout << *pi << ' ' << *pd << endl;
 pi = reinterpret_cast<int *>(&d);
 pd = reinterpret_cast<double *>(&i);
 cout << *pi << ' ' << *pd << endl;
 ia = reinterpret_cast<int>(&i);
 da = reinterpret_cast<int>(&d);
 pi = reinterpret_cast<int *>(ia);
 pd = reinterpret_cast<double *>(da);
 cout << *pi << ' ' << *pd << endl;
 i = d;
 d = i;
 cout << i << ' ' << d << endl;
 ia = reinterpret_cast<int>(&i);
 da = reinterpret_cast<int>(&d);
 pi = reinterpret_cast<int *>(ia);
 pd = reinterpret_cast<double *>(da);
 cout << *pi << ' ' << *pd << endl;
#else
 i = d;
 d = i;
#if 1
 d = reinterpret_cast<double>(i);
 i = reinterpret_cast<int>(d);
 d = reinterpret_cast<double>(&i);
 pi = reinterpret_cast<int *>(d);
 ia = reinterpret_cast<int>(&i);
 da = reinterpret_cast<int>(&d);
 cout << *pi << ' ' << *pd << endl;
#endif
 cout << i << ' ' << d << endl;
#endif
}
