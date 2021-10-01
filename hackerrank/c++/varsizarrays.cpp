#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

vector<vector<int> > parseLines()
{
    string l;
    vector<vector<int> > vvi;
    while(getline(cin, l))
    {
        stringstream ss(l);
        vector<int> vi;
        int i;
        while(ss >> i) {
            vi.push_back(i);
        }
        vvi.push_back(vi);
    }
    return vvi;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    vector<vector<int> > vvi(parseLines());
    int i(0), j(0);
    int na(vvi[i][j++]);     
    int nq(vvi[i++][j]);
    vector<vector<int> > a;
    a.reserve(na);
    int s(na + i);
    for (; i < s; ++i)
    {
	j = 0;
	vector<int> r;
	r.reserve(vvi[i][j++]);
	for (; j < vvi[i].size(); ++j)
	{
            r.push_back(vvi[i][j]);
	}
        a.push_back(r);
    } 
    vector<vector<int> > q;
    q.reserve(nq);
    s = nq + i;
    for (; i < s; ++i)
    {
        q.push_back(vvi[i]);
    } 
    for (int l(0); l < nq; ++l)
    {
	cout << a[q[l][0]][q[l][1]] << endl;
    }
    return 0;
}
