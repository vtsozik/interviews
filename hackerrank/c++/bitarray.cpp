#include <string.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct BitArray
{
    BitArray() : m_stor(new long[m_sts]) 
    {
        memset(m_stor, 0, m_sts * sizeof(m_stor[0]));
    }
    ~BitArray() 
    {
        delete[] m_stor;
    }
    void set(long n)
    {
        long ind = n / m_density;
	long r = n % m_density;
	m_stor[ind] |= (1 << r);
    }
    long get(long n)
    {
        long ind = n / m_density;
	long r = n % m_density;
	return m_stor[ind] & (1 << r);
    }
private:
    static const long m_density = sizeof(long) * 8;
    static const long m_sts = (1l << 31) / m_density;
    long* m_stor;
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    long n, s, p, q;
    cin >> n >> s >> p >> q;
    cout << "n = " << n << ", s = " << s << ", p = " << p << ", q = " << q << endl;
    long mdl(1l << 31);
    long a = s % mdl;
    long cnt(0);
    BitArray ba;
    for (long i(0); i < n; ++i)
    {
        if (!ba.get(a))
	{
            ++cnt;
	    ba.set(a);
	}
	a = (a * p + q) % mdl);
    }
    cout << cnt << endl;
    return 0;
}
