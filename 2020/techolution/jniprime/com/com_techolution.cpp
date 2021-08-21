#include "com_techolution.h"
#include <math.h>

/*
 * I provide a simple deterministic implementation of
 * primality test. Probabilistic algorithm will be better
 * for BigIntegers i.e. due high amount of fixed costs.
 * Please see my paper on Miller-Rabin optimization:
 * https://sites.google.com/site/vtsozik/papers/optimization-of-miller-rabin-algorithm-with-sieve-of-eratosthenes-accelerator 
 */
JNIEXPORT jboolean JNICALL Java_com_techolution_assignment
  (JNIEnv *e, jobject o, jint i)
{
    if (i <= 3)
    {
	// Primes are always greater than 1.
        return (i > 1);
    }

    // Even and devisible by 3 are composites.
    if (i % 2 == 0 || i % 3 == 0)
    {
        return false; 
    }

    /* We only need to test divisors up to square root as they are then
     * guaranteed to be unique.
     */
    int sr(sqrt(i));
    /* Since candidate is not divisable by 2 or 3 we can skip 
     * by 2 * 3 = 6. Also primes have often distance 2 between
     * them, we need to test that distance as well (5, 7), (11, 13),
     * (17, 19), (29, 31), etc.
     */
    for (int j(5); j <= sr; j += 6)
    {
        if (i % j == 0 || i % (j + 2) == 0)
	{
	    return false;
	}
    }
    return true;
}
