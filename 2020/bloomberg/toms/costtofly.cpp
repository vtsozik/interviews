/*
 * You are given a list of job candidates cost to fly to New York and San Francisco office
 * for job interviews: {{500, 600}, {1000, 700}, {200, 400}, {800, 300}, {100, 900}}
 * You need to equally distribute candidates between offices minimizing their cost to fly.
 */

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
using namespace std;

pair<vector<size_t>, vector<size_t> > distributecandidates(const vector<pair<int, int> > v)
{
    struct Compare
    {
        bool operator()(const pair<int, int>& left, const pair<int, int>& right) const
	{
	    return (left.first - left.second) < (right.first - right.second);
	}
    };
    multimap< pair<int, int>, size_t, Compare> mm;
    for (size_t i(0); i < v.size(); ++i)
    {
        mm.insert(make_pair(v[i], i));
    }
    pair<vector<size_t>, vector<size_t> > pv;
    size_t s(mm.size() / 2);
    pv.first.reserve(s);
    pv.second.reserve(s);
    auto fi = mm.begin();
    auto bi = mm.rbegin();
    for(size_t f(0), b(mm.size() - 1); f <= b; ++f, --b)
    {
        if (f < b)
        {
            pv.first.push_back(fi->second);
            pv.second.push_back(bi->second);
	}
	else if(fi->first.first < bi->first.second)
	{
            pv.first.push_back(fi->second);
	}
	else
	{
            pv.second.push_back(bi->second);
	}
	++fi;
	++bi;
    }
    return pv;
}

int main()
{
    vector<pair<int, int> > v = {{500, 600}, {1000, 700}, {200, 400}, {800, 300}, {100, 900}};
    pair<vector<size_t>, vector<size_t> > pv(distributecandidates(v));
    cout << "Candidate, New York, San Francisco" << endl;
    for (size_t i(0); i < v.size(); ++i)
    {
        cout << i << ",\t" << v[i].first << ",\t" << v[i].second << endl;
    }
    cout << "New York, San Francisco" << endl;
    for (size_t i(0), j(0); i < pv.first.size() || j < pv.second.size(); ++i, ++j)
    {
	if (i < pv.first.size())
	{
            cout << pv.first[i] << " -> " << v[pv.first[i]].first;
	}	    
	else
	{
	    cout << '\t';
	}
	cout << ", ";
	if (j < pv.second.size())
	{
	    cout << pv.second[j] << " -> " << v[pv.second[j]].second;
	}
	else
	{
	    cout << '\t';
	}
	cout << endl;
    }
    return 0;
}
