#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

/*
Idea: Let's call the target the distance between set I and set J D_IJ, and the whole set S.
Let's define similar distance WITHIN set I and set J, D_II, D_JJ.
There are countable ways to split the array, so there must be a case with minimum D_IJ.
It's easy to see D_SS = D_II + D_JJ + D_IJ, and D_SS is fixed for given S.
Then, the problem becomes maximizing D_II + D_JJ.

Let's look at where to put the smallest number a.

Let's first assmue a is in the array I, it sits at the beginning since it's the smallest.
Now let's look at the first (smallest) number b in array J.
We ask the question: if we switch a and b, does D_II+D_JJ become bigger or smaller?
This depends on the relative position of a and b in their sets.
Let's define d_ab = abs(a-b), array I has k numbers, array J has m=n-k numbers, then
D_II decreases by d_ab * (k-1), because the distance between a and everything else in I decrease by d_ab;
D_JJ increases by d_ab * (m-1), because the distance between b and everything else in J increase by d_ab;
if (d_ab * (k-1) < d_ab * (m-1)) or simply (k-1) < (m-1), D_II+D_JJ increases if a is switched to J, so a should be in J.
Once a is placed, check the second smallest number and so forth, until I has k numbers.

Here we call (k-1) and (m-1) weights for a and b, respectively.
Such weights are calculated based on relative position, for example:
For each position r in set I or J, if there are x numbers before it and y numbers after it, its weight is y-x, i.e. w[r] = y-x.
This logic is used to compute w1 and w2 in the code.

Once the weights are calculated for all positions, it's easy to place each number in sorted S in ascending order: bigger weight gets smaller number to maximize distance.
*/

int64_t fairCut(size_t k, vector<int> arr) {
    std::sort(arr.begin(), arr.end());
    size_t n(arr.size()), m(n - k);
    vector<int64_t> w1(k), w2(m);
    for (size_t i(0); i < k; i++)
    {
        w1[i] = k - 1 - 2 * i;
    }
    for (size_t i(0); i<m; i++)
    {
        w2[i] = m - 1 - 2 * i;
    }
    vector<int64_t> v1, v2;
    v1.reserve(k);
    v2.reserve(m);
    for (size_t l(0), i(0), j(0); i < k && j < m; ++l) {
        long a = arr[l];
        if (w1[i] > w2[j]) {
            v1.push_back(a);
            i++;
        } 
        else 
        {
            v2.push_back(a);
            j++;
        }
    }
    for (size_t l(n - (k - v1.size())); l < n; ++l)
    {
            v1.push_back(arr[l]);
    }
    for (size_t l(n - (m - v2.size())); l < n; ++l)
    {
            v2.push_back(arr[l]);
    }
    int64_t sum = 0;
    for (auto i : v1) {
        for (auto j : v2) {
            sum += abs(i-j);
        }
    }
    return sum;
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

