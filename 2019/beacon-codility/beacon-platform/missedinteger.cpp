#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm> 
using namespace std;

int solution(vector<int> &A) {
    if(A.empty())
        return 1;
    unordered_set<int> s;
    int max(0);
    for (int i(0); i < A.size(); ++i)
    {
        if(A[i] > 0) {
            if(A[i] > max) {
                max = A[i];
	    }
	    s.insert(A[i]);
	}
    }
    int t = 1;
    for(; t <= max; ++t)
    {
         if(s.find(t) == s.end())
             return t;
    }
    return t;
}

int main() {
 vector<int> a = {1, 3, 6, 4, 1, 2};
 cout << solution(a) << '\n';
 return 0;
}
