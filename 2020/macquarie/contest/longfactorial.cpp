#include <bits/stdc++.h>
#include <cstddef>

using namespace std;

struct BigInteger
{
    vector<char> val;

    BigInteger() : val() {}

    BigInteger(int n)
    {
        val.reserve(10);
        for (int i(n); i > 0; i /= 10)
        {
            val.push_back(static_cast<char>(i % 10));
        }
        if (val.empty())
        {
            val.push_back(0);
        }
    }
    BigInteger operator+(const BigInteger& right)
    {
        BigInteger result;
        size_t vs(val.size()), rvs(right.val.size()), ms(max(vs, rvs));
        result.val.reserve(ms + 1);
        for (size_t i(0); i < ms; ++i)
        {
            int a(0);
            if (i < vs)
            {
                a += static_cast<int>(val[i]);
            }
            if (i < rvs)
            {
                a += static_cast<int>(right.val[i]);
            }
	    if (i < result.val.size())
            {
                a += static_cast<int>(result.val[i]);
            }
            size_t j(i);
            do 
            {
                char cv = static_cast<char>(a % 10);
                if (j < result.val.size())
                {
                    result.val[j] = cv;
                }
                else 
                {
                    result.val.push_back(cv);
                }
                ++j;
                a /= 10;
            }
            while(a > 0);
        }
        return result; 
    }

    BigInteger multunit(int unit, size_t pos)
    {
        BigInteger result;
        result.val.insert(result.val.begin(), pos + 1, 0);
        size_t vs(val.size());
        for (size_t i(0); i < vs; ++i) 
        {
            int a(val[i] * unit);
            size_t j(i + pos);
            do {
              char cv = static_cast<char>(a % 10);
              if (j < result.val.size())
              {
                  result.val[j] += cv;
              } 
              else
              {
                  result.val.push_back(cv);
              }
              ++j;
              a /= 10;
            } while(a > 0);
        }
        return result;
    }

    BigInteger operator*(const BigInteger& right)
    {
        BigInteger result;
        size_t rvs(right.val.size());
        for (size_t i(0); i < rvs; ++i) 
        {
            BigInteger ur(multunit(static_cast<int>(right.val[i]), i));
            result = result + ur;
        }
        return result;
    }

    void print()
    {
        for (auto i(val.rbegin()); i != val.rend(); ++i)
        {
            cout << static_cast<int>(*i);
        }
        cout << endl;
    }
};

void extraLongFactorials(int n) {
    BigInteger r(1);
    for (int i(2); i <= n; ++i)
    {
        BigInteger n(i);
        r = n * r;
    }
    r.print();
}

int main()
{
    int64_t n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    extraLongFactorials(n);
    return 0;
}
