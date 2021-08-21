#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

template <class T> void inplqs(T *t, int left, int right);
extern template void inplqs<int>(int *t, int left, int right);

void findSumOfTwoInOn(const int * const a, const int n, const int sum) {
 int min(a[0]), max(min);
 for(int i(0); i < n; ++i) {
  if(a[i] < min) {
   min = a[i];
  } else if(a[i] > max) {
   max = a[i];
  }
 }
 int ni(max - min + 1), *ia = new int[ni], j;
 memset(ia, 0, ni * sizeof(ia[0])); 
 ia[a[0] - min] = 1;
 for(int i(1); i < n; ++i) {
  j = sum - a[i];
  if(min <= j && j <= max &&
   (j = ia[j - min])-- > 0) {
   cout << "Found elements:" << " a[" << i << "] = " << a[i] << " and"
    << " a[" << j << "] = " << a[j] << " with sum: "
    << a[i] + a[j] << " in O(n) time" << endl;
   break;  
  } else {
   ia[a[i] - min] = i + 1;
  }
 }
 delete[] ia;
}

void findSumOfTwoInOnLog2n(const int * const a, const int n, const int sum) {
 int ac[n], left(0), right(n - 1), s;
 memcpy(ac, a, n * sizeof(a[0]));
 inplqs<int>(ac, left, right); 
 cout << "Sorted array: ";
 for(int i(0); i < n; ++i) {
  cout << ac[i] << ' ';
 }
 cout << endl;
 while(left < right) {
  s = ac[left] + ac[right];
  if(s < sum) {
   ++left;
  } else if(s > sum) {
   --right;
  } else {
   cout << "Found elements:" << " ac[" << left << "] = " << ac[left] << " and" 
    << " ac[" << right << "] = " << ac[right] << " with sum: " 
    << ac[left] + ac[right] << " in O(n * log2(n)) time" << endl;
   break;  
  }
 } 
}

int main() {
 srand(time(NULL));
 static const int n(10), m(100);
 int a[n], first(rand() % n), second(rand() % n), sum;
 while(second == first) {
  second = rand() % n;
 }
 cout << "Array to search: ";
 for(int i(0); i < n; ++i) {
  a[i] = rand() % m;
  cout << a[i] << ' ';
 }
 cout << endl;
 sum = a[first] + a[second];
 cout << "Looking for elements:"
  << " a[" << first << "] = " << a[first] << " and"
  << " a[" << second << "] = " << a[second] 
  << " with sum: " << sum << endl;
 findSumOfTwoInOn(a, n, sum);
 findSumOfTwoInOnLog2n(a, n, sum);
}
