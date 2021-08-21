/*
 * Given an array of positive integers, find the closest pair. 
 * The closest pair has the smallest absolute value of the difference.
 * Input: {32,71,12,45,26,80,34,43} Output: 32,34
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void find_closest_pair(vector<int> array)
{
    if  (array.size() < 2)
    {
        cerr << "Invalid input" << endl;
        return;
    }
    sort(array.begin(), array.end());
    if (array.size() == 2)
    {
        cout << "Min pair: (" << array[0] << ',' << array[1] << ")" << endl;
        return;
    }
    int min(array[1] - array[0]);
    size_t min_li(0), min_ri(1);
    for(size_t i(2); i < array.size(); ++i)
    {
        int d = array[i] - array[i - 1];
        if (d < min)
        {
            min = d;
            min_li = i - 1;
            min_ri = i;
        }
    }
    cout << "Min pair: (" << array[min_li] << ',' << array[min_ri] << ")" << endl;
}

int main(int argc, char* argv[])
{
  int myints[] = {32,71,12,45,26,80,34,43};
  vector<int> array(myints, myints+8);
  find_closest_pair(array);
  
  return 0;
}
