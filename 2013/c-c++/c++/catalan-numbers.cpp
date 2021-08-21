#include <iostream>
using namespace std;

void printLegalParenthesisCombinations(string s, int current, int open, int total) {
 if(current == total) {
  cout << s << endl;
 } else {
  if(open < total / 2) {
   printLegalBracComb(s + '(', current + 1, open + 1, total);
  }
  if(current - open < open) {
   printLegalBracComb(s + ')', current + 1, open, total);
  }
 }
}


int main() {
 printLegalParenthesisCombinations("(", 1, 1, 8);
 return 0;
}
