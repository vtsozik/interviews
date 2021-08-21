#include <iostream>
using namespace std;

int solution(int A, int B) {
    // write your code in C++14 (g++ 6.2.0)
    int ub = 1;
    int rp = 0;
    for(; ub < B; ub *= 10, ++rp);
    int p = rp;
    int f = -1;
    for(int t = A; t >= B; ++p, t /= 10) {
        int mod = t % ub;
	cout << "mod = " << mod << " ub = " << ub << " p = " << p << endl;
        if (mod == B)
           f = p;
    }
    return (f < 0) ? f : p - f;
}

int main()
{
cout << solution(1953786, 53) << endl;
return 0;
}
