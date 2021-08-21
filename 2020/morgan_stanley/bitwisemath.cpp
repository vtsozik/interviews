#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    int v = 15 * 16 * 10;
    assert(v << 1 == 2 * v);
    assert(v << 4 == 16 * v);
    assert((v << 4) - v == 15 * v);
    assert(v >> 1 == v / 2);
    assert(v >> 4 == v / 16);
    /*
     * v / 15 = (v / 16) * (16 / 15) = (v / 16) * (1 / (15 / 16)) =
     * = (v / 16) * (1 / (1 - 1 / 16))
     * Now expand: 1 / (1 - 1/16) to 1 + 1/16 + (1/16)^2 + (1/16)^3 + ...,
     * Then v / 15 = v / 16 + v / (16)^2 + v / (16)^3 + ...
     */
    int t(v), s(0);
    while (t > 0)
    {
        t >>= 4;
	s += t;
    }
    cout << "v / 15 ~ " << s << ", v / 15 = " << v / 15 << ", v / 16 = " << v / 16 << endl;
    assert(v / 15 - s < v / 15 - v / 16);
}
