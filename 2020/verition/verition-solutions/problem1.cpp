/*
Find temperature reading anomalies in sensor data
____________________________________________________________________________

An industrial system subjects steel to a process called annealing
in which the steel is heated or cooled to harden it. A sensor is used
to record the system temperature in degrees Celsius at regular ten-minute
intervals starting from time zero. However, the sensor appears to be
malfunctioning and sometimes reporting readings much below actual temperature.
Let's call these anomalous temperature readings 'craters'.  Given a number
of time and temperature values, identify the craters and return both the time
and temperature values. A 'crater' is defined as a singular temperature reading
which is lower than the preceding and succeeding readings by a threshold value of
T degrees Celsius or greater.

____________________________________________________________________________

Given
* T: threshold, integer value in degrees Celsius, that determines whether
  a given temperature reading is a crater
* S: a list of time and temperature values, both integers: time in minutes
  from zero, temperature in degrees Celsius
 
Rules and Assumptions
* A crater would never occur on the first or last reading because its
  definition requires it to have neighboring values on the left and the right
* Craters always consist of only one reading lower than its two neighbors
  on either side, i.e. you will never see data like below:
  100,100,50,50,100
  Assume T = 30 for these readings. Then by definition, neither value of 50
  is a crater since it is not lower than both its neighbors by 30.
* There could be zero or one or more than one craters.
 
Example Input 1
Typical input looks like below: threshold first, followed by pairs of time
and temperature
35
0 121
10 122
20 50
30 123
40 121
50 80
60 120
70 119
80 121
 
Example Output 1
20 50
50 80
 
Example Input 2
This input has no craters
35
0 121
10 122
20 123
30 121
40 119
50 121
 
Example Output 2
No craters found!
 
Problem
Implement three functions, which are invoked from the main program:
1. A function to read from std::cin the threshold and the time and temperature pairs
   supplied as input and populate passed-in arguments (threshold and sensor data)
2. A function to find and return any craters found in the sensor data, which takes
   in as arguments, the threshold and sensor data read in
3. A function to write out the craters found to std::cout
*/

#include <iostream>
#include <utility>
#include <vector>
#include <sstream>

using namespace std;

/*
 * Complete the functions below.
 */

/*
 * read_sensor_data is expected to take 2 arguments and populate them by reading from std::cin
 * threshold - which defines a crater
 * sensor_data - a vector of time, temperature pairs
 */
void read_sensor_data(int& threshold, vector<pair<int, int>>& sensor_data)
{
 string line;
 int time, temp;
 if (getline(cin, line))
 {
  threshold = stoi(line);
  while (getline(cin, line))
  {
   std::istringstream iss(line);
   iss >> time >> temp;
   sensor_data.emplace_back(time, temp);
  }
 } 
}

/*
 * find_craters is expected to return a vector of integer-valued time,temperature pairs
 * representing the craters found in the input sensor data.
 * The function accepts a vector of integer-valued time,temperature pairs, and
 * a threshold that defines whether a given pair is a crater.
 */

vector<pair<int, int>> find_craters(const vector<pair<int,int>>& sensor_data, int threshold)
{
 size_t sz(sensor_data.size() - 1);
 int temp;
 std::vector<pair<int, int>> crtrs;
 crtrs.reserve(sz / 2);
 for (size_t i(1); i < sz; ++i)
 {
  temp = sensor_data[i].second;
  if (sensor_data[i - 1].second - temp < threshold)
  {
   continue;
  }
  if(sensor_data[i + 1].second - temp  < threshold)
  {
   i += 2;
   continue; 
  }
  crtrs.emplace_back(sensor_data[i].first, temp);
  ++i;
 }
 return std::move(crtrs);
}

/*
 * print_craters is expected to take 1 argument and write out its values to std::cout
 * sensor_data - a vector of time, temperature pairs
 * NB1: The time and temperature values must be separated by a single space
 * NB2: If the craters vector is empty, please print "No craters found!"
 */
void print_craters(const vector<pair<int, int>>& craters)
{
 if (craters.empty())
 {
  cout << "No craters found!" << std::endl;
  return;
 }
 for (const auto &i : craters)
 {
  std::cout << i.first << ' ' << i.second << std::endl;
 } 
}

int main()
{
    int threshold;
    vector<pair<int, int>> sensor_data;
                    
    read_sensor_data(threshold, sensor_data);

    vector<pair<int, int>> craters = find_craters(sensor_data, threshold);
                            
    print_craters(craters);
}
