#include <iostream>
#include <vector>
#include <set>
#include <list>
using namespace std;

int nonDivisibleSubset(int k, vector<int> s) 
{
    if (k == 1)
    {
        return 1;
    }
    vector<set<int> > mrs(100, set<int>());
    set<int> srs;
    vector<int> vrs;
    vrs.reserve(k);
    list<list<int> > rvis;
    for(size_t i(0); i < s.size(); ++i)
    {
	int r = s[i] % k;
	if ((2 * r) % k > 0 || mrs[r].size() < 1)
	{
            mrs[r].insert(s[i]);
	    if(srs.insert(r).second)
	    {
                vrs.push_back(r);
                rvis.push_back(list<int>(1, vrs.size() - 1));
	    }
	}
    }
    int mxs(vrs.size()), pmxs(0);
    if (mxs == 0)
    {
        return mxs;
    }
    else
    {
	mxs = mrs[vrs[0]].size();
	if (vrs.size() == 1)
	{
	    return mxs;
	}
    }
    list<list<int> > prvis;
    while (mxs > pmxs) 
    {
        prvis = rvis;
	rvis.clear();
	pmxs = mxs;
	mxs = 0;
	for (auto i(prvis.begin()); i != prvis.end(); ++i)
	{
            for (int j(*(i->rbegin()) + 1); j < vrs.size(); j++)
            {
                list<int> cl = *i;
	        auto l(cl.begin());
	        for (; l != cl.end(); ++l) 
	        {
                    if (vrs[*l] + vrs[j] == k)
                    {
                            break;
                    }
                }
	        if (l == cl.end())
	        {
                    cl.push_back(j);
                    rvis.push_back(cl);
	        }
	    }
        }
        for (auto i(rvis.begin()); i != rvis.end(); ++i)
        {
	    int sums(0);
            for (auto j(i->begin()); j != i->end(); ++j)
            {
                sums += mrs[vrs[*j]].size();
            }
	    if (mxs < sums)
	    {
	        mxs = sums;
	    }
        }
    }
    mxs = pmxs;
    rvis = prvis;
    int tot(0);
    for(size_t i(0); i < vrs.size(); ++i)
    {
        tot += mrs[vrs[i]].size();
        cout << "Reminder: " << vrs[i] << ", size: " << mrs[vrs[i]].size() << endl;
    }
    cout << "Total reminders: " << tot << ", combinations: " << rvis.size() << endl;
    for (auto i(rvis.begin()); i != rvis.end(); ++i)
    {
        for (auto j(i->begin()); j != i->end(); ++j)
	{
	    cout << ' ' << vrs[*j];
	}
        cout << endl;
    }

    return mxs;
}

int main()
{
    vector<int> a = {61197933,56459859,319018589,271720536,358582070,849720202,481165658,675266245,541667092,615618805,129027583,755570852,437001718,86763458,791564527,163795318,981341013,516958303,592324531,611671866,157795445,718701842,773810960,72800260,281252802,404319361,757224413,682600363,606641861,986674925,176725535,256166138,827035972,124896145,37969090,136814243,274957936,980688849,293456190,141209943,346065260,550594766,132159011,491368651,3772767,131852400,633124868,148168785,339205816,705527969,551343090,824338597,241776176,286091680,919941899,728704934,37548669,513249437,888944501,239457900,977532594,140391002,260004333,911069927,586821751,113740158,370372870,97014913,28011421,489017248,492953261,73530695,27277034,570013262,81306939,519086053,993680429,599609256,639477062,677313848,950497430,672417749,266140123,601572332,273157042,777834449,123586826};
    cout << nonDivisibleSubset(9, a) << endl;
    cout << "Correct answer: 50" << endl;
    // should be 50
    a = {2, 7, 12, 17, 22};
    cout << nonDivisibleSubset(5, a) << endl;
    cout << "Correct answer: 5" << endl;
    // should be 5
    a = {1, 2, 3, 4, 5};
    cout << nonDivisibleSubset(1, a) << endl;
    cout << "Correct answer: 1" << endl;
    // should be 1
    a = {1,2,3,4,5,6,7,8,9,10};
    cout << nonDivisibleSubset(4, a) << endl;
    cout << "Correct answer: 5" << endl;
    //should be 5
    return 0;
}
