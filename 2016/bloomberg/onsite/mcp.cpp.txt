/*
 * Question:
 *
 * Given matrix of numbers that represent cost of getting into its element 
 * calculate minimum cost path from element 0,0 to the last element of 
 * that matrix.
 *
 * Answer:
 *
 * Problem could be solved recursively as in examples minCostE (from the 
 * end) or minCostB (from the beginning). Somehow Bloomberg interviewer 
 * Sunil, didn't understand this and was convinced that only walk from the
 * end to the beginning is only possible recursive solution. (I didn't argue 
 * with him. Later I saw similar problem on 
 * http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path/
 * and realized that he even didn't bother to change the costs on the matrix. 
 * I left them the same too, but for a different reason, to verify the 
 * results against existing solutions). Recursive solution is exponentially 
 * expensive as we need to compute upto (m x n) costs upto (m x n) times, 
 * where m and n matrix dimensions. However with the assumption that we can 
 * only move from the upper element down in the same column or from the left 
 * element right in the same row or move one element diagonally, we allocate 
 * matrix of the same size and record into it cumulative costs of going 
 * through each element in first row and first column. Then we compute 
 * cumulative costs of getting into second diagonal element from first 
 * diagonal or via second element in first row or via second element in first 
 * column. We compare those costs and record the minimum into second diagonal 
 * element of the cumulative cost matrix. This will complete first (2 x 2) 
 * sub-matrix. Continue computing and recording minimum cumulative costs for 
 * all of the elements that are not in first row or first column. Resulted 
 * matrix will contain minimum cumulative cost of getting into the 
 * corresponding element. Print last element of this matrix as a minimum
 * cumulative costs of getting into the last element of the matrix. 
 *
 * Iterative solution represents good example of dynamic programming.
 *
 * Compile this program with:
 *  g++ -O3  mcp.cpp
 *
 * Run the resulted binary with:
 *  ./a.out 
 *
 * Observe expected output:
 *  Min cost path from the beginning: 8
 *  Min cost path from the end: 8
 *  Min cost path iterative: 8
 *
 */

#include <iostream>
#include <limits.h>
using namespace std;

#define R 3
#define C 3

int min(int a, int b, int c) {
 if(a < b) {
  return (c < a) ? c : a;
 } else {
  return (c < b) ? c : b;
 }
}

int minCostE(int m[R][C], int i, int j) {
 if(i < 0 || j < 0) {
  return INT_MAX;
 } else if(i == 0 && j == 0) {
  return m[i][j];
 } else {
  return m[i][j] + min(minCostE(m, i - 1, j),
                       minCostE(m, i - 1, j - 1),
                       minCostE(m, i, j - 1));
 }
}

int minCostB(int m[R][C], int i, int j) {
 if(i >= R || j >= C) {
  return INT_MAX;
 } else if(i == R - 1 && j == C - 1) {
  return m[i][j];
 } else {
  return m[i][j] + min(minCostB(m, i + 1, j),
                       minCostB(m, i + 1, j + 1),
                       minCostB(m, i, j + 1));
 }
}

int minCostI(int m[R][C]) {
 int c[R][C];
 c[0][0] = m[0][0];
 for(int i(1); i < R; ++i) {
  c[i][0] = c[i - 1][0] + m[i][0];
 }
 for(int j(1); j < C; ++j) {
  c[0][j] = c[0][j - 1] + m[0][j];
 }
 for(int i(1); i < R; ++i) { 
  for(int j(1); j < C; ++j) { 
   c[i][j] = m[i][j] + min(c[i - 1][j], c[i - 1][j - 1], c[i][j - 1]);
  }
 }
 return c[R - 1][C - 1];
}

int main() {
 int m[R][C] =  { {1, 2, 3},
                  {4, 8, 2},
                  {1, 5, 3} }; 
 cout << "Min cost path from the beginning: " << minCostB(m, 0, 0) << endl;
 cout << "Min cost path from the end: " << minCostE(m, R - 1, C - 1) << endl;
 cout << "Min cost path iterative: " << minCostI(m) << endl;
 return 0;
}
