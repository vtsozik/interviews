#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;

struct VarLenStrComp: public binary_function<string, string, bool> {
 bool m_isPartialCompare;
 void setPartialCompare(bool isPartialCompare) { m_isPartialCompare = isPartialCompare; }
 bool operator()(const string &s1, const string &s2) const {
  if(m_isPartialCompare) {
   size_t i(0), l(min(s1.length(), s2.length()));
   for(; i < l; ++i) {
    if(s1[i] != s2[i]) {
     break;
    }
   }
   return (i < l && s1[i] < s2[i]);
  } else {
   return s1 < s2;
  }
 }
};

int main() {
 string str("abcdefghij"), ss("abcji");
 VarLenStrComp varLenStrComp;
//#define LOGIC_DEBUG
#ifdef LOGIC_DEBUG 
 cout << str << (varLenStrComp(str, ss) ?  " less than " : (varLenStrComp(ss, str) ? " greater than " : " equal to ")) << ss << endl;
 varLenStrComp.setPartialCompare(true);
 cout << str << (varLenStrComp(str, ss) ?  " less than " : (varLenStrComp(ss, str) ? " greater than " : " equal to ")) << ss << endl;
#else
 set<string, VarLenStrComp&> dict(varLenStrComp);
 int i(0), n(10000), m(10);
 do {
//cout << "Inserting: " << str << endl;
  dict.insert(str);
 } while(next_permutation(str.begin(), str.end()) && ++i < n);
 cout << "Sorted dictionary elements:" << endl;
 set<string>::const_iterator iter = dict.begin();
 for(; iter != dict.end(); ++iter) {
  cout << *iter << endl;
 }
 cout << "Auto-completion search for " << ss << " string:" << endl;
 varLenStrComp.setPartialCompare(true);
 iter = dict.find(ss);
 for(i = 0; i < m && iter != dict.end(); ++i, ++iter) {
  cout << *iter << endl;
 } 
 cout << "limited to " << i << " results" << endl; 
#endif
 return 0;
}
