/*
 * Given 2 ordered vectors of numerical primitives find an intersection between them.
 */

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <iterator>
using namespace std;

template <class T, class U, class V> void intersection(T ti, T te, U ui, U ue, V vi)
{
    for (;ti != te && ui != ue;)
    {
        if(*ti < *ui)
        {
            ++ti;
        }
        else if (*ti > *ui) 
        {
           ++ui;
        }
        else
        {
           *vi = *ti;
           ++ti;
           ++ui;
        }
    }
}

int main()
{
    vector<int> a = {1, 2, 3, 4, 5, 6, 7};
    vector<int> b = {4, 5, 6, 7, 8, 9};
    vector<int> rv;
    back_insert_iterator<vector<int>> vii(rv);
    intersection(a.begin(), a.end(), b.begin(), b.end(), vii);
    cout << "vector" << endl;
    for (auto v : rv)
    {
        cout << v << endl;
    } 
    list<int> rl;
    insert_iterator<list<int>> lii(rl, rl.begin());
    intersection(a.begin(), a.end(), b.begin(), b.end(), lii);
    cout << "list" << endl;
    for (auto v : rl)
    {
        cout << v << endl;
    } 
    set<int> rs;
    insert_iterator<set<int>> sii(rs, rs.begin());
    intersection(a.begin(), a.end(), b.begin(), b.end(), sii);
    cout << "set" << endl;
    for (auto v : rs)
    {
        cout << v << endl;
    } 
    return 0;
}


