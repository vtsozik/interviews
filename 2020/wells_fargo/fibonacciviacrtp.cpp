#include <iostream>
using namespace std;

template<long n> struct Fib 
{
    static constexpr long value = Fib<n - 1>::value + Fib<n - 2>::value;
};

template<> struct Fib<0>
{
    static constexpr long value = 0;
};

template<> struct Fib<1>
{
    static constexpr long value = 1;
};

int main()
{
    cout << Fib<7>::value << endl;
    return 0;
}

