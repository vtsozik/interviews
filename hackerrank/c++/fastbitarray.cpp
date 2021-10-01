#include <string.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    long n, s, p, q;
    cin >> n >> s >> p >> q;
    long mdl(1l << 31), a0(s % mdl), a(a0), ap(a), i(0);
    for (; i < n; ++i)
    {
	cout << a << endl;
        if ((a == a0 || (a == ap)) && i > 0)
	{
	    break;
	}
	ap = a;
	a = (a * p + q) % mdl;
    }
    cout << i << endl;
    return 0;
}
