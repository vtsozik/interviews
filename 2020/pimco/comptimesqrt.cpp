#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    /* please see .LC0 -> 2 and .LC1 -> 2^0.5 labels in resulted assembly
     * as a proof of compile time evaluation of sqrt(constant).
     * you can use https://babbage.cs.qc.cuny.edu/IEEE-754.old/Decimal.html
     * to convert 2x32-bit longs from .LC1 to double. It accepts 64-bit value
     * made up from those longs converted to hex and concatenated to together.
     */
    constexpr double a = 2;
    constexpr double sqrt2 = sqrt(a);
    cout << "sqrt(" << a << ") = " << sqrt2 << endl;
    return 0;
}
