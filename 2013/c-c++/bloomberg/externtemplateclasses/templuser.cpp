#include "templdecl.h"
#include <iostream>
using namespace std;

extern template int size<int>(const int &i);

int main() {
 cout << size(7) << endl;
}
