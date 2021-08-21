#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int finducoupledint(const vector<int> v)
{
     int r = v[0];
     for (size_t i(1); i < v.size(); ++i)
     {
         r ^= v[i];
     }
     return r;
}

int main()
{
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<int> v;
    string delim;
    int e;
    while (ss)
    {
        ss >> e;
	v.push_back(e);
	ss >> delim;
    }

    cout << finducoupledint(v) << endl;
    return 0;
}
