#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

/*
 * Complete the fairCut function below.
 */
int64_t fairCut(int k, vector<int> arr) {
    sort(arr.begin(), arr.end());
    int64_t n(arr.size()), n1(n + 1);
    vector<int64_t> dpr(n, INT64_MAX);
    vector<vector<int64_t> > dp(n1, dpr);
    if (k > n / 2)
    {
     k = n - k;
    }
    dp[0][0] = 0;
    for(int64_t i(0); i < n; ++i)
    {
        for(int64_t j(0); j < i + 1; ++j)
        {
            if (j > k || i - j > n - k)
            {
                continue;
            }
            int64_t lu = dp[i][j] + arr[i] * (j - (k - j));
            int64_t li = dp[i][j] + arr[i] * (i - j - (n - k - (i - j)));
            if (dp[i + 1][j + 1] > li)
            {
                dp[i + 1][j + 1] = li;
            }
            if (dp[i + 1][j] > lu)
            {
                dp[i + 1][j] = lu;
            }   
        }
    }
    return dp[n][k];
}

int main()
{
    const char* pOp = getenv("OUTPUT_PATH");
    string sOp(pOp && strlen(pOp) > 0 ? pOp : "/dev/stdout");
    ofstream fout(sOp);

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int arr_itr = 0; arr_itr < n; arr_itr++) {
        int arr_item = stoi(arr_temp[arr_itr]);

        arr[arr_itr] = arr_item;
    }

    int64_t result = fairCut(k, arr);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
