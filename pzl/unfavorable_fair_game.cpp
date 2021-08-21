#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <stdlib.h>
using namespace std;

#define ub 1000
#define ns 1000000

int main() {
 vector<double> v;
 multimap<double, int> mm;
 int i;
 double sum = 0, p;
 v.reserve(ub + 1);
 v.push_back(0);
 for(i = 1; i <= ub; ++i) {
  p = 1 / pow(2, i) / i / (i + 1);
  v.push_back(p);
  sum += p;
 }
 v[0] = 1 - sum;
 sum = 0;
 for(i = 0; i <= ub; ++i) {
  sum += v[i];
  mm.insert(make_pair(sum, i));
//cout << "K = " << i << "; P(K) = " << sum << endl;
 }
 sum = 0;
 srand48(time(NULL));
 for(i = 0; i < ns; ++i) {
  p = drand48();
  multimap<double, int>::const_iterator cimm = mm.lower_bound(p);
  sum -= 1;
  if(cimm->second > 0) {
   sum += pow(2, cimm->second);
  }
//cout << "Ps(Ks) = " << p << "; Ks = " << cimm->second << "; S = " << sum << endl;
 } 
 cout << "S = " << sum << endl;
 return 0;
}
