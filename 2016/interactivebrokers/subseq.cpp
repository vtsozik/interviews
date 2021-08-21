#include <iostream>
#include <vector>
using namespace std;

void print_longest_contiguous(const vector<int> &v) {
 size_t start(0), end(0), max_start(0), max_end(0);
 for(size_t i(1); i < v.size(); ++i) {
  int difference = v[i] - v[i - 1];
  if(difference * difference == 1) {
   int direction = (v[end] - v[start]) * difference; 
   end = i;
   if(direction <= 0) {
    start = i - 1;
   }
   if(max_end - max_start < end - start) {
    max_start = start;
    max_end = end;
   }
  } else {
   start = end = 0;
  }
 }
 cout << "Longest contiguous subsequence: ";
 for(size_t i(max_start); i <= max_end; ++i) {
  cout << v[i] << ' ';
 }
 cout << endl;
}

int main() {
 vector<int> v = { 4, 2, 1, 2, 3, 4, 3, 5, 1, 2, 4, 6, 5 };
 print_longest_contiguous(v);
 return 0;
}
