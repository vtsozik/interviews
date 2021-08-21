/*
Find max number of squares that a integer can be exponentiated to be between ints A and B.
example: A = 9, b = 21: 3*3 = 9, (2*2)*(2*2)=16, answer is 2.
*/
#include <iostream>
using namespace std;

int solution(int A, int B) {
    int max = 0;
    for (int i = 2; i <= B; ++i) {
	int n = 0;
        for (int j = i; j <= B; j *= j, ++n) {
            if (j >= A) {
                if (n > max) {
                    max = n;
	        }
            }
        }
	if (n < max)
	    break;
    }
    return max;
}

int main() {
    cout << solution(9, 21) << endl;
    return 0;
}
