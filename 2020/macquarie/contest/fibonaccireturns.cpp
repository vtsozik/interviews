/* 
 * WARNING, VERY IMPORTANT NOTE:
 * This code uses BigInteger struct to represent large integer values (> 2^64 -1).
 * As test cases for large ns will fail if uint64_t type is used instead.
 * Python version (fibonaccireturns.py) passes all test cases as it internally
 * uses 128 bit _int128_t type to store Fn m_val. 
 *
 * Problem is given with contradicting initial conditions:
 * n <= 99 and Fn <= 2^64 - 1, so this implies that Fn(n=99) can be stored 
 * in 64 bit uint64_t type!
 *
 * Close form solution for Fibonacci:
 * Fn = ((1+sqrt(5))^n - (1-sqrt(5))^n)/((2^n)*sqrt(5))
 *  ~ ((1+sqrt(5))/(2*(5^(1/2*n))))^n ~ 1.605^n
 *  Now if upper bound n = 99, then then log2(1.605)^99 
 *  = 99*log2(1.605) = 99*0.6826 = 67.58
 *
 * So roughly we need 68 bits to store upper bound Fn(n=99)!
 *
 * While long double type is 80 bits in C++ it only provides 64 bit for 
 * precision, as it also needs 15 bits for exponent and 1 bit for sign.
 * (Please see IEEE-754 extended precision format for further details
 * on long double encoding.)
 */

#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <assert.h>

using namespace std;

struct BigInteger
{
    bool m_isNegative;
    vector<int8_t> m_val;

    BigInteger() : m_isNegative(false), m_val() {}

    BigInteger(int n) : m_isNegative(n < 0)
    {
	n = abs(n);
        m_val.reserve(10);
        for (int i(n); i > 0; i /= 10)
        {
            m_val.push_back(static_cast<int8_t>(i % 10));
        }
        if (m_val.empty())
        {
            m_val.push_back(0);
        }
    }
    int getInteger() const
    {
	int a(0), p(1);
        for (size_t i(0); i < m_val.size(); ++i)
	{
	    a += m_val[i] * p;
	    p *= 10;
	}
	return a;
    }
    BigInteger operator+(const BigInteger& right) const
    {
        BigInteger result;
	if (m_isNegative == right.m_isNegative)
	{
            result.m_isNegative = m_isNegative;
	}
	else
	{
            if (m_isNegative) 
	    {
	        BigInteger bi(*this);
		bi.m_isNegative = false;
	        return right.operator-(bi);
	    }
            else
	    {
	        BigInteger bi(right);
                bi.m_isNegative = false;
		return operator-(bi);
	    }
	}
        size_t vs(m_val.size()), rvs(right.m_val.size()), ms(max(vs, rvs));
        result.m_val.reserve(ms + 1);
        for (size_t i(0); i < ms; ++i)
        {
            int a(0);
            if (i < vs)
            {
                a += static_cast<int>(m_val[i]);
            }
            if (i < rvs)
            {
                a += static_cast<int>(right.m_val[i]);
            }
	    if (i < result.m_val.size())
	    {
                a += static_cast<int>(result.m_val[i]);
	    }
            size_t j(i);
            do
            {
                int8_t bv = static_cast<int8_t>(a % 10);
                if (j < result.m_val.size())
                {
                    result.m_val[j] = bv;
                }
                else
                {
                    result.m_val.push_back(bv);
                }
                ++j;
                a /= 10;
            }
            while(a > 0);
        }
        return result;
    }
    BigInteger operator-(const BigInteger& right) const
    {
        BigInteger result;
        if (m_isNegative != right.m_isNegative)
        {
            BigInteger bi(right);
	    bi.m_isNegative = m_isNegative;
            return operator+(bi);
        }
        else if (m_isNegative)
        {
            BigInteger rbi(right);
            rbi.m_isNegative = false;
            BigInteger lbi(*this);
            lbi.m_isNegative = false;
	    return rbi.operator-(lbi);
        }
	if (operator<(right))
	{
            BigInteger r = right.operator-(*this);
	    r.m_isNegative = true;
	    return r;
	}
        size_t vs(m_val.size()), rvs(right.m_val.size());
        result.m_val.reserve(vs);
        for (size_t i(0); i < vs; ++i)
        {
            int a = static_cast<int>((i < result.m_val.size()) ? result.m_val[i] : m_val[i]);
            if (i < rvs)
            {
                a -= static_cast<int>(right.m_val[i]);
            }
	    if (a < 0 && i + 1 < vs)
            {
                a += 10;
		if (i < result.m_val.size())
		{
                    result.m_val[i] = static_cast<int8_t>(a);
		}
		else
		{
                    result.m_val.push_back(static_cast<int8_t>(a));
		}
		if (i < vs - 2 || m_val[i + 1] > 1)
		{
		    result.m_val.push_back(m_val[i + 1] - 1);
		    continue;
		}
		break;
            }
	    result.m_isNegative = (a < 0);
            if (i < result.m_val.size())
	    {
                result.m_val[i] = static_cast<int8_t>(abs(a));
	    }
	    else
            {
                result.m_val.push_back(static_cast<int8_t>(abs(a)));
            }
        }
        return result;
 
    }
    bool operator<(const BigInteger& right) const
    {
	if (m_isNegative == right.m_isNegative)
	{
            if (m_val.size() == right.m_val.size())
    	    {
                for (size_t i(m_val.size() - 1); i < m_val.size(); --i)
                {
                    if (m_val[i] == right.m_val[i])
    		    {
                        continue;
    		    } 
                    return (m_isNegative) ? (right.m_val[i] < m_val[i]) : (m_val[i] < right.m_val[i]);
                }
    	    }
	}
    	return (m_isNegative) ? (right.m_val.size() < m_val.size()) : (m_val.size() < right.m_val.size());
    }
};

ostream& operator<<(ostream& o, const BigInteger& bi)
{
    if (bi.m_isNegative)
    {
        o << '-';
    }
    for (auto i(bi.m_val.rbegin()); i != bi.m_val.rend(); ++i)
    {
        o << static_cast<int>(*i);
    }
    return o;
}

BigInteger fib(BigInteger n, map<BigInteger, BigInteger>& m)
{
    if (BigInteger(1) < n)
    {
        auto i = m.find(n);
	if (i != m.end())
	{
	    return i->second;
	}
        BigInteger r(fib(n - 1, m) + fib(n - 2, m)); 
	m.insert(pair<BigInteger, BigInteger>(n, r));
        return r;
    }
    return n;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    map<BigInteger, BigInteger> m;
    string s; 
    while (getline(cin, s))
    {
        cout << fib(atoi(s.c_str()), m) << endl;
    }
    return 0;
}
