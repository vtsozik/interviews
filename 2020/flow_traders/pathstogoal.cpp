#include <bits/stdc++.h>
using namespace std;

static const int mod = 1000000007;

int distinctMovesStartingFromLeft(string s, int i, int n, int x, int y);

int distinctMovesStartingFromRight(string s, int i, int n, int x, int y) {
    if (n < x || x < 0 || i >= s.size())
        return 0;
    if (s[i] == 'r')
	return (++x == y ? 1 : 0) + distinctMovesStartingFromRight(s, ++i, n, x, y) % mod + distinctMovesStartingFromLeft(s, i, n, x, y) % mod;
    return distinctMovesStartingFromRight(s, ++i, n, x, y) % mod;
}

int distinctMovesStartingFromLeft(string s, int i, int n, int x, int y) {
    if (n < x || x < 0 || i >= s.size())
        return 0;
    if (s[i] == 'l')
        return (--x == y ? 1 : 0) + distinctMovesStartingFromLeft(s, ++i, n, x, y) % mod + distinctMovesStartingFromRight(s, i, n, x, y) % mod;
    return distinctMovesStartingFromLeft(s, ++i, n, x, y) % mod;
}

int distinctMoves(string s, int n, int x, int y)
{
    return ((x == y ? 1 : 0) + distinctMovesStartingFromRight(s, 0, n, x, y) + distinctMovesStartingFromLeft(s, 0, n, x, y)) % mod;
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
