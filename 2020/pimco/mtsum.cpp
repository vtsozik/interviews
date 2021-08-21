#include <thread>
#include <future>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
using namespace std;

inline void accum(promise<uint64_t>&& p, const vector<uint64_t> &vals, size_t start, size_t end) 
{
    auto vit(vals.begin());
    p.set_value(accumulate(vit + start, vit + end, 0));
}

int main()
{
    constexpr size_t n(1000000);
    constexpr size_t nthrs(6);
    vector<uint64_t> values(n, 0);
    iota(values.begin(), values.end(), 1);
    list<future<uint64_t> > futs;
    vector<thread> thrs;
    thrs.reserve(nthrs);
    constexpr size_t batch_size(n / nthrs);
    for (size_t i(0), j(0); i < nthrs; ++i)
    {
        promise<uint64_t> p;
        futs.push_back(p.get_future());
	size_t nj(j + ((i == 0) ? (n - (nthrs - 1) * batch_size) : batch_size));
        thrs.push_back(thread(accum, move(p), values, j, nj));
	j = nj;
    }
    size_t sum(0);
    while(!futs.empty())
    {
        for (auto lit(futs.begin()); lit != futs.end(); ++lit)
        {
	    if (lit->wait_for(chrono::nanoseconds(0)) == future_status::ready) // primitive poll
	    {
                sum += lit->get();
		futs.erase(lit);
		break;
	    }
	}
    }  
    cout << "SUM: " << sum << endl;
    for_each(thrs.begin(), thrs.end(), [](thread& t) { t.join(); }); // housekeeping
    return 0;
}
