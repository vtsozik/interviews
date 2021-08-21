#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

uint64_t fib(uint64_t n)
{
    if (n > 1)
    {
        return fib(n - 1) + fib(n - 2);
    }
    return n;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << fib(n) << endl;

    return 0;
}
