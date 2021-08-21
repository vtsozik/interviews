#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'changeAds' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER base10 as parameter.
 */

int changeAds(int base10) {

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string base10_temp;
    getline(cin, base10_temp);

    int base10 = stoi(ltrim(rtrim(base10_temp)));

    int result = changeAds(base10);

    fout << result << "\n";

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
