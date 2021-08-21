#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define K 2
#define M 6
#define N 10

typedef vector<int> vint;

struct cless {
 bool operator() (const vint& lhs, const vint& rhs) const {
  for(int i = 0; i < M; ++i) {
   if(lhs[i] > rhs[i]) {
    return false;
   } else if(lhs[i] < rhs[i]) {
    return true;
   }
  }
  return false;
 }
};

typedef set<vector<int>, cless> cset;

struct MoutofN {
 vint vi;
 cset cs;
 MoutofN() {
  vi.reserve(N);
  int js = N / K;
  for(int i = 0; i < js; ++i) {
   for(int j = 0; j < K; ++j) {
    vi.push_back(i);
    cout << i << ' ';
   } 
  }
    cout << endl;;
 }
 int Run() {
  cs.clear();
  do {  
   cs.insert(vi);
  } while(next_permutation(vi.begin(), vi.end()));
  return cs.size();
 }
};

int main() {
 MoutofN mn;
 cout << mn.Run() << endl;
}
