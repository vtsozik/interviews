#include <iostream>
#include <string>
using namespace std;

int main() {
 char *c = "foo";
 string s("foo");
//#define TEMPLATE_DEDUCTION_ERROR
#ifdef TEMPLATE_DEDUCTION_ERROR
 bool res = *c == s;
#else
/*

 For the line below the following overloaded operator will be invoked:

 <std::operator==<char, std::char_traits<char>, std::allocator<char> >(char const*, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)>

*/
 bool res = c == s;
#endif
 cout << "res = " << (res ? "true" : "false") << endl; 
 return 0;
}
