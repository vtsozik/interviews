#include <iostream>
using namespace std;

template <class T> bool greaterS(const T &t1, const T &t2) {
 return t1 < t2;
}

template <class T1, class T2> bool greaterD(const T1 &t1, const T2 &t2) {
 return t1 < t2;
}

int main() {
 cout << "Single greaterS<int>(3, 5.): " << greaterS<int>(3, 5.) << endl;
 cout << "Double greaterD<int, double>(3, 5.): " << greaterD<int, double>(3, 5.) << endl;
 return 0;
}
