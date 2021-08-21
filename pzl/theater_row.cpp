/*
 * * Question:
 * * Theater row has 15 seats and randomly ticketed to 8 boys and 7 girls.
 * * How many girl-boy and boy-girl couples at average this random
 * * seating arrangement will yield?
 * *
 * * Answer:
 * * This problem has the following recursive solution:
 * * Exected number of couples can be computed using the following recursive relations:
 * * N(m, w) = M(m, w) + W(m, w), where
 * * Expected number of couples where man sits before woman:
 * * M(m, w) = m / (m + w) * (w / (m + w - 1) * (1 + N(m -1, w - 1)) + M(m - 1, w)) 
 * * Expected number of couples where woman sits before man:
 * * W(m, w) = w / (m + w) * (m / (m + w - 1) * (1 + N(m -1, w - 1)) + W(m, w - 1)) 
 * * Also note, that recursion tree is recombining, hence complexity is ~O(n^2).
 * * This solution is encapsulated into EnhancedRow class (see C++ code below). 
 * */

#include <stdlib.h>
#include <iostream>
using namespace std;

class EnhancedRow {
 int m_, w_;
 inline double GetSingleProbability(int n, int m, int w) {
  return static_cast<double>(n) / static_cast<double>(m + w);
 }
 double GetMaleBranchProbability(int m, int w) {
  if(m < 1 || w < 1) {
   return 0.;
  }
  double mp, fp;
  mp = GetSingleProbability(m, m, w);
  fp = GetSingleProbability(w, m - 1, w);
  return mp * (fp * (1. + GetPairProbability(m - 1, w - 1)) + GetMaleBranchProbability(m - 1, w));
 }
 double GetFemaleBranchProbability(int m, int w) {
  if(m < 1 || w < 1) {
   return 0.;
  }
  double fp, mp;
  fp = GetSingleProbability(w, m, w);
  mp = GetSingleProbability(m, m, w - 1);
  return fp * (mp * (1. + GetPairProbability(m - 1, w - 1)) + GetFemaleBranchProbability(m, w - 1));
 }
 double GetPairProbability(int m, int w) {
  return GetMaleBranchProbability(m, w) + GetFemaleBranchProbability(m, w);
 }
public:
 EnhancedRow(int m, int w) : m_(m), w_(w) {}
 double ComputeExpectedCouples() {
  return GetPairProbability(m_, w_);
 }
};

int main(int argc, char **argv) {
 if(argc != 3) {
  cout << "Usage: " << argv[0] << " <Number of men> <Number Of Women>" << endl;
  return 1;
 }
 EnhancedRow er(atoi(argv[1]), atoi(argv[2]));
 cout << "Expected Number Of Couples: " << er.ComputeExpectedCouples() << endl;
 return 0;
}

