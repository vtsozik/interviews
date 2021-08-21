#include <bits/stdc++.h>
using namespace std;

static const int mod = 1000000007;

int distinctMoves(string s, int i, int n, int x, int y, bool inclr) {
    if (n < x || x < 0)
    {
        return 0;
    }
    if (i < s.size())
    {
        int t(x);
        if (s[i] == 'r' && inclr)
        {
            ++t;
        }
        else if (s[i] == 'l' && !inclr)
        {
            --t;
        }
	else
	{
            return distinctMoves(s, i + 1, n, t, y, inclr) % mod;
	}
        return ((t == y ?  1 : 0) + distinctMoves(s, i + 1, n, t, y, inclr) % mod + distinctMoves(s, i + 1, n, t, y, !inclr) % mod);
    }
    return 0;
}

int distinctMoves(string s, int n, int x, int y)
{
    return ((x == y ? 1 : 0) + distinctMoves(s, 0, n, x, y, true) + distinctMoves(s, 0, n, x, y, false)) % mod;
}

int main()
{
    string s;
    cin >> s;

    int n;
    cin >> n;

    int x;
    cin >> x;


    int y;
    cin >> y;

    cout << distinctMoves(s, n, x, y) << endl;
    return 0;
}
