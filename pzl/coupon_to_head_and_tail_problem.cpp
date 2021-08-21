/*
Q: You throw fair coin until sequence contains atleast 1 head and 1 tail. 
1) How many times you need to throw on average to meet the condition above?
2) How many times you need to throw to meet the condition above with 90% 
confidence?
A: 1) We can adapt a solution to coupon collector problem. For first throw
We're guaranteed to get unique value (head or tail) and we need to throw only 
2/2=1 time to get first unique value. For second throw we may need to throw 
2/(2-1)=2 times to get unique value, so we need to throw 1+2=3 times on average
to get unique value.
2) Let's derive probability that we stop exactly at nth throw. We need to make 
at least 2 throws to have atleast 1 head and 1 tail in resulted sequence. After
second throw only 2 out of 4 sequence combinations will contain both head and 
tail, so probability to stop at second throw is P(2)=2/4=1/2. Probability that 
we do not stop at second throw will be also P'(2)=1-1/2=1/2. Probality that we
stop at exactly at third throw will be equal to P(3)=P'(2)*1/2=1/2*1/2=1/4, 
since probability that we get head or tail that will compliment existing tail 
or head sequence respectively is equal to 1/2 for a fair coin. Now the 
probability that we don't meet stoping condition at third throw is also equal 
to 1/2, so probability that we don't stop at third throw is equal to 
P'(3)=P'(2)*1/2=1/4. Consequently for fourth throw we have P(4)=P'(3)*1/2=1/8 
and P'(4)=P'(3)*1/2=1/8. Now ith throw we will have P(i)=P'(i)=(1/2)^(i-1). For 
average number of throws to stop we will have N=sum[i=2,inf](i*(1/2)^(i-1)).
If we replace 1/2 with x then it's easy to see that N=sum[i=2,inf](i*(x)^(i-1))
=sum[i=2,inf](d(x^i)/di)=d(sum[i=2,inf](x^i))/di=d((1-(x^n))/(1-x))/dx-1
=d(1/(1-x))/dx-d((x^n)/(1-x))/dx-1=(1-x)^(-2)-(n*x^(n-1))/(1-x)-(x^n)/(1-x)^2
-1. Since x=1/2 and n->infinity N=(1-(1/2))^(-2)-0-0-1=4-1=3. To find number of
throws to achieve 90% confidence that the resulted sequence will have at least 1 tail and 1 head we simply need to solve the following equation for X:
(1-(1/2)^(X-1))/(1-(1/2))-1=0.9. This is because cummulative distribution 
function for probability to stop before or at nth throw is equal to CDF(N)
=sum[i=2,N]((1/2)^(i-1))=(1-(1/2)^(N-1))/(1-(1/2))-1. So we have
1-(1/2)^(X-1)=1.9/2 and (1/2)^(X-1)=0.05 leads to X=5.322 throws.
*/

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <set>
using namespace std;

int main() {
 srand(time(NULL)); 
 int n(1000000), states(2), count;
 double avg(0), e(0), ptostop(1.0/states), apl(0), apm(0), ape(0);
 for(int i(2); ptostop >= 10e-6; ++i) {
  e += (double) i * ptostop;
  ptostop /= states;
 }
 for(int i(0); i < n; ++i) {
  count = 0;
  set<bool> s;
  do {
   s.insert(rand() < RAND_MAX / states); 
   ++count;
  } while(s.size() < states);
  avg += count;
  if(count < e) {
   ++apl;
  } else if(count > e) {
   ++apm;
  } else {
   ++ape;
  }
 }
 avg /= n;
 apl /= n;
 apm /= n;
 ape /= n;
 cout << "Average: " << avg << ", Expectation " << e << endl
  << ", Associated Probability Less: " << apl << endl
  << ", Associated Probability More: " << apm << endl
  << ", Associated Probability Equal: " << ape << endl
  << ", Less Plus More, Plus Equal: " << apl + apm + ape << endl;
 return 0;
}
