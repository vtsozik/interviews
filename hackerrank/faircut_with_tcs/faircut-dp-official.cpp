#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int64_t test(const vector<int> &arr, const set<size_t> &sinds)
{
 int64_t sum(0);
 for (auto i : sinds)
 {
  for (size_t j(0); j < arr.size(); ++j)
  {
   if (sinds.find(j) == sinds.end())
   {
    sum += abs(arr[i] - arr[j]);
   }
  }
 }
 return sum;
}

int64_t validate(const vector<int> &arr, int k)
{
 int64_t minDiff(INT64_MAX);
 size_t n(arr.size());
 set<size_t> testSet, minSet;
 vector<bool> combs(n);
 fill(combs.begin(), combs.begin() + k, true);
 do
 {
  testSet.clear();
  for (size_t i(0); i < n; ++i)
  {
   if (combs[i])
   {
     testSet.insert(i);
   }
  }
  int64_t diff(test(arr, testSet));
  if (diff < minDiff)
  {
   minDiff = diff;
   minSet = testSet;
  }
 }
 while (prev_permutation(combs.begin(), combs.end()));
 for (auto &e : minSet)
 {
  cout << "arr[" << e << "] = " << arr[e] << ", ";
 }
 cout << minDiff << endl;
 return minDiff;
}

int64_t fairCut(int k, vector<int> arr) {
 int64_t n(arr.size()), m(k + 1);
 vector<int64_t> dr(m, INT64_MAX);
 vector<vector<int64_t> > dm(n, dr);
 sort(arr.begin(), arr.end());
 for (int64_t i(0); i < n; ++i)
 {
  if (i == 0)
  {
   dm[0][0] = dm[0][1] = 0;
  }
  else
  {
   for (int64_t j(max(0l, (k - (n - i - 1)))); j < m; ++j)
   {
    if (dm[i - 1][j] != INT64_MAX)
    {
     dm[i][j] = dm[i - 1][j] + (arr[i] - arr[i - 1]) * j * (n - i - (k - j)) + (arr[i] - arr[i - 1]) * (i - j) * (k - j);
    }
   }
   for (int64_t j(max(0l, k - (n - i))); j < k; ++j)
   {
    if (dm[i - 1][j] != INT64_MAX)
    {
     if (dm[i][j + 1] == INT64_MAX)
     {
      dm[i][j + 1] = dm[i - 1][j] + (arr[i] - arr[i - 1]) * (j * (n - i - (k - j)) + (i - j) * (k - j));
     }
     else
     {
      dm[i][j + 1] = min(dm[i][j + 1], dm[i - 1][j] + (arr[i] - arr[i - 1]) * (j * (n - i - (k - j)) + (i - j) * (k - j)));
     }
    }
   }
  }
 }
 //cout << "minDiff = " << dm[n - 1][k] << endl;
 //validate(arr, k);
 return dm[n - 1][k];
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

    for (int64_t arr_itr = 0; arr_itr < n; arr_itr++) {
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
