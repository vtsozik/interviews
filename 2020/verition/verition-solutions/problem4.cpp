/*
Maximize total number of coins
____________________________________________________________________________

Imagine an m x n matrix with each cell containing certain number of coins. You
are standing at (0,0), and can only walk down or right one step a time. As you
walking towards the destination (m-1,n-1), you pick coins in each cell along
the path. The goal is to maximize the number of coins you collect on the way
to the destination.
____________________________________________________________________________

Given
* The dimensions of the matrix (m,n)
* The matrix of integers, each cell value represents the number of coins it contains
 
Rules and Assumptions
* Start from (0,0), end at (m-1,n-1)
* You can only walk down or right

Example Input 1
3 4
1 3 2 5
4 3 1 6
3 7 3 2
 
Example Output 1
20

Explanation 1
The optimal path is 1-4-3-7-3-2, which adds to 20.
All other paths result in number of coins less than 20.

Example Input 2
3 4
1 3 2 5
4 3 1 6
3 0 3 2
 
Example Output 2
19

Explanation 2
The optimal path is 1-3-2-5-6-2, which adds to 19.
All other paths result in number of coins less than 19.
 
Problem
Implement two functions, which are invoked from the main program:
1. A function to read from std::cin the dimension of the matrix and the matrix itself
2. A function to return the maximum number of coins along all paths
*/

#include <iostream>
#include <limits>
#include <vector>
#include <sstream>
#include <cassert>

using namespace std;

/*
 * Implement the functions below
 */

/*
 * read_matrix is expected to take 1 argument and populate it by reading from std::cin
 * It reads in the matrix dimensions and the matrix values
 */

void read_matrix(vector<vector<int>>& matrix)
{
 string line;
 int m, n, v;
 if (getline(cin, line))
 {
  istringstream iss(line);
  iss >> m >> n;
  matrix.reserve(m);
  while (getline(cin, line))
  {
   istringstream iss(line);
   vector<int> r;
   r.reserve(n);
   while (iss >> v)
   {
    r.emplace_back(v);
   }
   assert(r.size() == n);
   matrix.emplace_back(r);
  }
  assert(matrix.size() == m);
 }
}

int maximize_coins(const vector<vector<int>>& matrix, size_t i, size_t j, size_t m, size_t n,
                   vector<vector<int>>& memo)
{
 if (i < m && j < n)
 {
  if (memo[i][j] == -1)
  {
   int c(maximize_coins(matrix, i, j + 1, m, n, memo));
   int r(maximize_coins(matrix, i + 1, j, m, n, memo));
   memo[i][j] = matrix[i][j] + ((c > r) ? c : r);
  }
  return memo[i][j];
 }
 return 0;
}

/*
 * maximize_coins is expected to take 1 argument and compute the highest number
 * of coins that can be collected while traversing from (0,0) to (m-1,n-1)
 * incrementing either the row or column index by 1, but not both simultaneously
 */

int maximize_coins(const vector<vector<int>>& matrix)
{
 size_t m(matrix.size());
 if (m == 0)
 {
  return 0;
 }
 size_t n(matrix[0].size());
 if (n == 0)
 {
  return 0;
 }
 vector<int> mr(n, -1);
 vector<vector<int>> memo(m, mr);
 return maximize_coins(matrix, 0, 0, m, n, memo);
}

int main()
{
    vector<vector<int>> matrix;
                    
    read_matrix(matrix);

    auto coins_collected = maximize_coins(matrix);
                            
    cout << coins_collected << endl;
}
