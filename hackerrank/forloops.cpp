#include <iostream>
#include <cstdio>
#include <limits>
#include <string>
using namespace std;

int main() {
    // Complete the code.
    int j(0);
    long n[2];
    string l;
    while(getline(cin, l))
    {
        sscanf(l.c_str(), "%ld", &(n[j++]));
    }

    string s[9] = {"one", "two", "three", "four", "five", 
                   "six", "seven", "eight", "nine"};

    for (long i = n[0]; i <= n[1]; ++i)
    {
        if ( i > 9 )
        {
            cout << ((i % 2) ? "odd" : "even") << endl;
        }
        else
        {
            cout << s[i - 1] << endl;       
        }
    };

    return 0;
}
