#include <string.h>
#include <iostream>
using namespace std;

void reverse_word(char *s) {
 if(!s) {
  return;
 }
 char t;
 int l = strlen(s);
 for(int i = 0, j = l; i < j; ++i, --j) {
  t = s[j];
  s[j] = s[i]; 
  s[i] = t;
 } 
}

int main() {
 char *s = "Hello";
 reverse_word(s);
 cout << s << endl;
 return 0;
}
//"Hello world" -> "world hello"


