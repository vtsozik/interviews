#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct Key {
    Key(int n, vector<long> c) : m_n(n), m_c(c) {}
    bool operator<(const Key& right) const
    {
        if (m_n == right.m_n)
        {
            if(m_c.size() == right.m_c.size())
            {
                for (size_t i(0); i < m_c.size(); ++i)
		{
                    if (m_c[i] == right.m_c[i])
                    {
                        continue;
                    }
		    return m_c[i] < right.m_c[i];
                }
            }
	    return m_c.size() < right.m_c.size();
        }
	return m_n < right.m_n;
    }
    int m_n;
    vector<long> m_c;
};

long getWaysMemo(int n, vector<long> c, map<Key, long>& m) {
   if (n == 0)
   {
       return 1;
   }
   if (n < 0)
   {
       return 0;
   }
   long s(0);
   if (c.size() > 0)
   {
      Key k(n, c);
      auto mi = m.find(k);
      if (mi != m.end())
      {
          return mi->second;
      }
      s += getWaysMemo(n - c.back(), c, m);
      c.pop_back();
      s += getWaysMemo(n, c, m);
      m.insert(pair<Key, long>(k, s));
   }
   return s;
}

/*
 * Complete the 'getWays' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. LONG_INTEGER_ARRAY c
 */

long getWays(int n, vector<long> c) {
   map<Key, long> mcc;
   return getWaysMemo(n, c, mcc);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    string c_temp_temp;
    getline(cin, c_temp_temp);

    vector<string> c_temp = split(rtrim(c_temp_temp));

    vector<long> c(m);

    for (int i = 0; i < m; i++) {
        long c_item = stol(c_temp[i]);

        c[i] = c_item;
    }

    // Print the number of ways of making change for 'n' units using coins having the values given by 'c'
    
    long ways = getWays(n, c);

    fout << ways << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
