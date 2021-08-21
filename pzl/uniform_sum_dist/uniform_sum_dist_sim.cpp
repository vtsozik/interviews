#include <stdlib.h>
#include <iostream>
using namespace std;

int main() {
 srand48(time(NULL));
 int i, j;
 double m1 = 0, m2 = 0, s, n = 1e9;
 for(i = 0; i < (int) n; ++i) {
  s = 0;
  for(j = 0; s < 1; ++j) {
   s += drand48();
  }
  m1 += (double) j / n;
  m2 += (s - 1) / n;
 }
 cout.precision(40);
 cout.setf(ios::fixed,ios::floatfield);
 cout << "m1 = " << m1 << ", m2 = " << m2 << ", m1*m2 = " << m1 * m2 << endl;
 return 0;
}

// Results: m1 = 2.7182560534363084947528932389104738831520, m2 = 0.3591407076597040171073160763626219704747, m1*m2 = 0.9762364026313899989517608446476515382528
