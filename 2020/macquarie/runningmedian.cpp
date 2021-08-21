#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

template <class T> void printRA(T& t, const char* l)
{
    cout << l << ':';
    for (size_t i(0); i < t.size(); ++i)
    {
        cout << ' ' << t[i];
    }
    cout << endl;
}

vector<double> runningMedian(vector<int>& a) 
{
    /*
     * Write your code here.
     */
    auto minHeapComp = [&](int m, int n)-> bool {
        return m > n; 
    };
    vector<int> minHeap, maxHeap;
    vector<double> rngMed;
    size_t s(a.size());
    minHeap.reserve(s / 2 + 1);
    maxHeap.reserve(minHeap.capacity());
    rngMed.reserve(s);
    for (size_t i(0); i < s; ++i)
    {
        if (minHeap.empty())
        {
            minHeap.push_back(a[i]);
        } 
	else if (maxHeap.empty())
        {
            maxHeap.push_back(a[i]);
            if (minHeap.front() < maxHeap.front())
            {
                swap(minHeap[0], maxHeap[0]);
            }
        } 
	else if (a[i] >= minHeap.front())
        {
            minHeap.push_back(a[i]);
            push_heap(minHeap.begin(), minHeap.end(), minHeapComp);
        }
        else
        {
            maxHeap.push_back(a[i]);
            push_heap(maxHeap.begin(), maxHeap.end());
        }
        while (minHeap.size() > maxHeap.size() + 1)
        {
            maxHeap.push_back(minHeap.front());
            push_heap(maxHeap.begin(), maxHeap.end());
            pop_heap(minHeap.begin(), minHeap.end(), minHeapComp);
            minHeap.pop_back();
        }
        while (minHeap.size() + 1 < maxHeap.size())
        {
            minHeap.push_back(maxHeap.front());
            push_heap(minHeap.begin(), minHeap.end(), minHeapComp);
            pop_heap(maxHeap.begin(), maxHeap.end());
            maxHeap.pop_back();

        }
        if (minHeap.size() > maxHeap.size())
        {
            rngMed.push_back(minHeap.front());
        }
        else if (maxHeap.size() > minHeap.size())
        {
            rngMed.push_back(maxHeap.front());
        }
        else
        {
            rngMed.push_back(static_cast<double>(maxHeap.front() +
                minHeap.front()) / 2.);
        }
    }
    return rngMed;
}

int main()
{
    vector<int> v;
    for (size_t i(1); i <= 10; ++i)
    {
	v.push_back(i);
    }
    vector<double> r(runningMedian(v));
    printRA(r, "Result");
    return 0;
}
