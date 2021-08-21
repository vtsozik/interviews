#include <cmath>
#include <cstdio>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

void fizzbuzz(int n)
{
    vector<pair<int, string>> dm = {{3,"Fizz"}, {5, "Buzz"}};
    for (int i(1); i <= n; ++i)
    {
	stringstream ss;
        auto dmi(dm.begin());
	for(; dmi != dm.end(); ++dmi)
	{
	    if (i % dmi->first == 0)
	    {
	        ss << dmi->second;
	    }
	}
	if (ss.str().empty())
	{
            ss << i;
	}
        cout << ss.str() << endl;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    fizzbuzz(n);    

    return 0;
}

