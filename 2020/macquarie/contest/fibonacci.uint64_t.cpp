/* 
 * WARNING, VERY IMPORTANT NOTE:
 * This code for demo onlyThis code for C++ demo only. It fails test cases for 
 * large n's. Please use Python version (fibonacci.py) instead as it internally
 * uses 128 bit int128_t data type to store Fn value. 
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
#include <unordered_map>

using namespace std;

uint64_t fib(uint64_t n, unordered_map<uint64_t, uint64_t>& m)
{ 
    if (n > 1)
    {
        auto i = m.find(n);
	if (i != m.end())
	{
	    return i->second;
	}
        uint64_t r = fib(n - 1, m) + fib(n - 2, m); 
	m.insert(pair<uint64_t, uint64_t>(n, r));
        return r;
    }
    return n;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    unordered_map<uint64_t, uint64_t> m;
    string s; 
    while (getline(cin, s))
    {
        cout << fib(atoll(s.c_str()), m) << endl;
    }
    return 0;
}
