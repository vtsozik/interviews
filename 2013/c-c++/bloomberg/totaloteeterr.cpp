#include <iostream>
using namespace std;

char getFirstSingleChar(const char *str) {
 int b['Z' - 'A' + 1];
 int size(sizeof(b) / sizeof(b[0]));
 //cout << size << endl;
 for(int i(0); i < size; ++i) { 
  b[i] = 0; 
 }
 for(int i(0); str[i] != '\0'; ++i) { 
  ++b[str[i] - 'A'];
 }
 for(int i = 0; str[i] != '\0'; ++i) { 
  if(b[str[i] - 'A'] == 1) {
   return str[i]; 
  }
 }
 return '\0';
}

int main() {
 const char *str[2] = {"TOTAL", "TEETER"};
 int size(sizeof(str) / sizeof(str[0]));
 for(int i(0); i < size; ++i) { 
  cout << str[i] << " -> " << getFirstSingleChar(str[i]) << endl;
 }
}
