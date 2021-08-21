#include <bits/stdc++.h>
using namespace std;

vector< vector< vector <int> > > v;
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
            int cnt(distinctMoves(s, i + 1, n, t, y, inclr) % mod);
	    cout << "s = " << s.substr(i + 1) << ", x = " << t << ", y = " << y << ", s[0] = " << s[i] << ", inclr = " << inclr << ", cnt = " << cnt << endl;
	    v[i][x][inclr] += cnt;
	    return cnt;
	}
	int cnt1(t == y ?  1 : 0);
	int cnt2(distinctMoves(s, i + 1, n, t, y, inclr));
	int cnt3(distinctMoves(s, i + 1, n, t, y, !inclr));
	cout << "s = " << s.substr(i + 1) << ", x = " << t << ", y = " << y << ", s[0] = " << s[i] << ", inclr = " << inclr << endl;
	cout << "cnt1 = " << cnt1 << ", cnt2 = " << cnt2 << ", cnt3 = " << cnt3 << endl;
	v[i][x][inclr] += cnt1 + cnt2 + cnt3;
        return cnt1 + cnt2 + cnt3;
    }
    return 0;
}

int distinctMoves(string s, int n, int x, int y)
{
    int cnt1(x == y ?  1 : 0);
    int cnt2(distinctMoves(s, 0, n, x, y, true));
    int cnt3(distinctMoves(s, 0, n, x, y, false));
    cout << "Final: cnt1 = " << cnt1 << ", cnt2 = " << cnt2 << ", cnt3 = " << cnt3 << endl;
    for (size_t i(0); i < v.size(); ++i)
    {
        for (size_t j(0); j < v[i].size(); ++j)
	{
            cout << '[' << v[i][j][0] << ',' << v[i][j][1] << "]; ";
	}
	cout << endl;
    }
    return cnt1 + cnt2 + cnt3;
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

    vector<int> v1 = {0, 0};
    vector<vector<int>> v2(s.size(), v1);
    v.insert(v.end(), s.size(), v2);
    cout << distinctMoves(s, n, x, y) << endl;
    return 0;
}
