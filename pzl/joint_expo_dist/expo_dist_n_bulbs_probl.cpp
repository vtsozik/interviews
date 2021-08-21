#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

const double mr = RAND_MAX, b = 1e-9;

inline double getrand() {
 double r = ((double) rand()) / mr;
 if(r == 1.) {
  r -= b;
 }
 return r;
}

int main() {
 srand(time(NULL));
 const int n = 1000000, v = 4;
 double tmin, tmax, t, m = 1000000., mins = 0., maxs = 0.;
 for(int i = 0; i < n; ++i) {
  tmin = 1 / b;
  tmax = 0.;
  for(int j = 0; j < v; ++j) { 
   t = -log(1. - getrand());
   if(tmin > t) {
    tmin = t;
   }
   if(tmax < t) {
    tmax = t;
   }
  }
  mins += tmin / (double) n;
  maxs += tmax / (double) n;
 }
 mins *= m;
 maxs *= m;
 cout << "Average life: serial: " << mins << " hours, parallel: " << maxs << " hours." << endl;
 return 0;
}

