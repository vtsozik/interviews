/*
 * You are given a map of islands in the ocean where island land markied 
 * as 1 and ocean surface mrked as 0. Count number of islands.
 */

#include <vector>
#include <iostream>
using namespace std;

bool isIsland(vector<vector<bool> > &m, size_t i, size_t j, size_t s)
{
    bool result = false;
    if (i < s && j < s)
    {
        result = m[i][j];
        if(result)
        {
            m[i][j] = 0;
            isIsland(m, i, ++j, s);
            isIsland(m, ++i, j, s);
            isIsland(m, ++i, --j, s);
            isIsland(m, ++i, ++j, s);
        }
    }
    return result;
}

size_t count_islands(vector<vector<bool> > &m)
{
    size_t cnt = 0;
    size_t s = m.size();
    for (size_t i(0); i < s; ++i)
    {
        for (size_t j(0); j < s; ++j)
        {
            if (isIsland(m, i, j, s))
            {
                ++cnt;
            }
        }
    }
    return cnt;
}

int main()
{
    // C++ 11 intitalizer list
    vector<vector<bool> > m =
    {
        { 0, 1, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 1 },
        { 0, 1, 1, 0, 1, 0, 0, 1 },
        { 0, 1, 0, 1, 1, 1, 0, 1 },
        { 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 0, 0, 1, 1, 1, 0 }
    };
    cout << count_islands(m) << endl; // prints 7 in this case.
    return 0;
}
