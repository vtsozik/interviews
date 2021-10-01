#include <bits/c++config.h>
#include <bits/stdc++.h>

using namespace std;

// Complete the appendAndDelete function below.
string appendAndDelete(string s, string t, int k) {
    size_t sl(s.length()), tl(t.length());
    int overlap(0);
    for(size_t i(0), j(0); i < sl && j < tl; ++i, ++j)
    {
        if (s[i] == s[j])
        {
            ++overlap;
        }
        else 
        {
            break;
        }
    }
    cout << "overlap = " << 
    return ((sl + tl - 2 * overlap) <= k) ? "Yes" : "No";
}

int main()
{
    string result = appendAndDelete("qwerasdf", "qwerbsdf", 6);

    cout << result << "\n";


    return 0;
}
