#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

/*
 * Eventhough -16 <= x <= 16 I used 2^16 denominator and 16 iteration loop
 * for better precision. 16 iterations is maximum for compiler (g++) to unroll
 * fast exponentiation loop. 
 * I added parsing value from command line to prevent compilie-time evaluation
 * when 4 level of optimization is used (-O4).
 * fexp ~2-3 times faster with -O4 and 4-5 times faster with -O0.
 */
inline double fexp(double x)
{
    double e = (1. + x / 65536);
    for (size_t i(0); i < 16; ++i)
    {
        e *= e;
    }
    return e;
}

int main(int c, char** args)
{
    double x(8.8);
    // Command line arg supresses compile time computation with -O4
    if (c == 2)
    {
        x = atof(args[1]);
    }
    struct timespec t1, t2, t3;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t1);
    double r(exp(x));
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t2);
    double fr(fexp(x));
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t3);
    cout << "fexp(" << x << ") = " << fr 
	 << ", exp(" << x << ") = " << r << endl;
    cout << "fexp(" << x << ") took: " 
	 << t3.tv_nsec - t2.tv_nsec
	 << ", exp(" << x << ") took: "
	 << t2.tv_nsec - t1.tv_nsec
	 << " nanoseconds." << endl;
    return 0;
}
