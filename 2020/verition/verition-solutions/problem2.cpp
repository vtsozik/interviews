/*

Find the longest intersection of several line segments
____________________________________________________________________________

Consider a set of line segments.
Each segment is identified by a starting X coordinate and an ending X coordinate.
The task at hand is to compute the length of the longest intersection between
any two segments.
____________________________________________________________________________

Rules
The segments are given in random order
Each segment may intersect with more than one other segment
 
Example Input 1
4 15
3 16
1 2
22 33
7 25
 
Example Output 1
11
 
Example Input 2
1 2
3 4
5 6
 
Example Output 2
0
 
Problem
Implement two functions, which are invoked from the main program:
1. A function to read from std::cin the segments, with their start and end X coordinates
2. A function to find and return the length of the maximum intersection between any two segments
 
NB: You may add any additional convenience functions to carry out specific computations you need as required.

*/

#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

/*
 * Complete the functions below.
 * Feel free to add any helper functions you need.
 */

/*
 * read_segments is expected to take 1 arguments and populate it by reading from std::cin
 * segments - a vector of x1, x2 integer-valued segment start and end X coordinates
 */

void read_segments(vector<pair<int, int>>& segments)
{
 string line;
 int x1, x2;
 while (getline(cin, line))
 {
  std::istringstream iss(line);
  iss >> x1 >> x2;
  segments.emplace_back(x1, x2);
 }
}

/*
 * max_intersection takes a vector of segments and returns
 * the length of the longest intersection.
 * NB: the argument is non-const
 */

int max_intersection(vector<pair<int,int>>& segments)
{
 int mi(0);
 sort(segments.begin(), segments.end(), [](const std::pair<int, int> &l, const std::pair<int, int> &r) {
  return l.first < r.first;
 });
 for (size_t i(1), j(0); i < segments.size(); ++i)
 {
  if (segments[j].second <= segments[i].first)
  {
   ++j;
   continue;
  }
  int inter(std::min(segments[j].second, segments[i].second) - segments[i].first);
  if (inter > mi)
  {
   mi = inter;
   continue;
  }
  if(segments[j].second <= segments[i].second)
  {
   j = i;
  }
 }
 return mi;
}

int main()
{
    vector<pair<int, int>> segments;
                
    read_segments(segments);

    int length = max_intersection(segments);
                        
    cout << length << endl;

    return 0;
}
