#include <vector>
#include <iostream>
using namespace std;

#define SEQLEN 100

#if 1
int main() {
 int i, j, n = SEQLEN;
 vector<double> c(n), p(n);
 c[0] = p[0] = 1.;
 for(i = 1; i < n; ++i) {
  for(j = 1; j < i; ++j) {
   c[j] = (i * p[j] + p[j - 1]) / (i + 1);
  } 
  c[j] = p[j - 1] / (i + 1);
  p ;
 }
 for(i = 0; i < n; ++i) {
  cout << "Record length: " << i + 1 << "\tCumulative probability: " <<  c[i] << endl; 
 } 
 return 0;
}
#else
#include <stdlib.h>
int main() {
 int i, j, r, s = 0, m = SEQLEN, n = 1000000; 
 double max, t, aa = 0, as = 0;
 vector<double> c(m, 0);
 for(i = 1; i <= m; ++i) {
  aa += 1. / i;
 } 
 cout << "Average record length (analytic):\t" << aa << endl;
 srand48(time(NULL)); 
 c[0] = 1.;
 for(i = 0; i < n; ++i) {
  r = 1;
  max = drand48();
  for(j = 1; j < m; ++j) {
   t = drand48();
   if(max < t) {
    max = t;
    ++r;
   }
  }
  as += ((double) r) / n;
  for(j = 1; j < r; ++j) {
   c[j] += 1. / n;
  }
 }
 cout << "Average record length (simulation):\t" << as << endl;
 for(i = 0; i < m; ++i) {
  cout << "Record length: " << i + 1 << "\tCumulative probability: " <<  c[i] << endl; 
 }
 return 0;
}
#endif

#if 0
Q1: You have a sequence of n random numbers? How many records at average this sequence will have. Number is a record if it is greater than 
each previous number in a given sequence.
A1: Any sequence will have at least one record (i.e. maximum value), so the probability of having one record in a sequence is equal to one. 
Then probability to have second record is equal to one half, because it is equally likely that second maximum is located before or after 
first maximum, but we only can count it as a second record if it's located after first maximum. Probability of having third record is equal 
to one third because it may be located before first maximum or between first and second maximum or after second maximum. Again we can count 
it as third record only if it's located after second maximum in a given sequence. Expanding this logic further probability of having fourth 
record is equal to one fourth, since fourth maximum can be equally likely located before first, between first and second, between second and 
third or after third maximum. But we only can count it as fourth record if it's located after this record. From the above we can conclude 
that expected number of records will be equal to sum of harmonic series: E[r] = sum[i = 1, n]((1 / i) * 1) = sum[i = 1, n](1 / i). 
Q2: What will be cumulative probability of having J or more records in a sequence of I random numbers? Again number can be counted as a 
record if it is greater than each previous number in a given sequence.
A2: See the upper part of C++ code above. If CDF(I, J) is cumulative probability of having J or more number of records in a sequence of I 
random numbers then the following recurrence relations exist:
1) For I = (1, n) and J = 1, CDF(I, J) = 1
2) For I = (2, n) and J = (2, I - 1), CDF(I, J) = ((I - 1) * CDF(I - 1, J) + CDF(I - 1, J - 1)) / I
3) For I = (2, n) and J = I, CDF(I, J) = CDF(I - 1, J - 1) / I 
Recurrence relations in 2) and 3) we can be backwarded:
4) For I = (2, n) and J = (2, I - 1), CDF(I - 1, J - 1) = I * CDF(I, J) - (I - 1) * CDF(I - 1, J)
5) For I = (2, n) and J = I, CDF(I - 1, J - 1) = I * CDF(I, J)
Also note that in both 2) and 3) CDF is divided by I - sequence length, every time when sequence length I is increased by 1.
#endif
