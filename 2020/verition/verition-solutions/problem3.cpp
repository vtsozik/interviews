/*
Maximize profit in stock trading
____________________________________________________________________________

Given a time series of stock prices, find the best trading strategy to maximize
profit with at most one buy and one sell. The buy has to come before the sell,
meaning that you cannot sell a stock you don't have already.
____________________________________________________________________________

Given
* An array of integers representing the stock tick prices
 
Rules and Assumptions
* Buy action has to come before sell
* If there is no opportunity to realize positive profit,
  you don't have to buy or sell: Return 0 in this case
 
Example Input 1
10 11 9 14 13 10 13
 
Example Output 1
5
 
Example Input 2
10 12 16 9 10 12
 
Example Output 2
6

Example Input 3
10 9 9 8 7

Example Output 3
0
 
Problem
Implement two functions, which are invoked from the main program:
1. A function to read from std::cin the time series of stock prices
2. A function to find the maximum profit from the time series
*/

#include <iostream>
#include <limits>
#include <vector>
#include <sstream>

using namespace std;

/*
 * Complete the functions below.
 */

/*
 * read_prices is expected to take 1 argument and populate it by reading from std::cin
 * prices - a vector of stock prices
 */

void read_prices(vector<int>& prices)
{
 int p;
 while(cin >> p) 
 {
  prices.emplace_back(p);
 }
}

/*
 * maximize_profit is expected to take 1 argument and compute the maximum possible profit
 * from buying and then subsequently selling the stock given its price history
 * prices - a const vector of stock prices
 */

int maximize_profit(const vector<int>& prices)
{
 if (prices.empty())
 {
  return 0;
 }
 int mp(0), buy(prices[0]), sell;
 for (size_t i(1); i < prices.size(); ++i)
 {
  sell = prices[i];
  if (sell <= buy) 
  {
   buy = sell;
   continue;
  }
  int prof(sell - buy);
  if (mp < prof)
  {
   mp = prof;
  } 
 }
 return mp;
}

int main()
{
    vector<int> prices;
                    
    read_prices(prices);

    auto max_profit = maximize_profit(prices);
                            
    cout << max_profit << endl;
}
