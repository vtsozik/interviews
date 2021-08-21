#include <iostream>
using namespace std;

/*
#define fib1(n) ((n > 1) ? (fib1(n - 1) + fib1(n - 2)) : 1)
#define fib1(n) n                                                               
*/

template<unsigned t> struct fib {
 static const unsigned r = fib<t - 1>::r + fib<t - 2>::r;
};                                                                                                                                                           
template<> struct fib<0> {
 static const unsigned r = 0;
};                                                                                                                                                           
template<> struct fib<1> {
 static const unsigned r = 1;
};                                                                                                                                                           
int main() {
 const unsigned n = 7;
 unsigned s;
 //s = fib1(n);
 s = fib<n>::r;
 cout << "fib1(" << n << ") = " << s << endl;
 return 0;
}         
