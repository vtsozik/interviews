//Computing the ratio of quantities has many use cases in finance. A simple ratio calcuation of 2 numbers can be done easily however when the calculation invovles more numbers it can get interesting. Let's take an example of analyzing a stock. A public company has n number of shares, it earns x dollars in a year. You can compute its earning per share (eps) by computing x over n. If the company has a stock price of p dollars then you can further compute a price to earning per share ratio (p/e) by computing p over eps. Further more, if there is an other company you can also compute a ratio of their p/e's. This is one way to compare valuation of different companies (who is expensive and who is cheap)

#include <iostream>
#include <memory>
#include <cassert>
using namespace std;

class Data
{
public:
  Data(double value) : p_value(new double(value)) {}
  Data(shared_ptr<double> pvalue, const Data& data2) : p_value(pvalue), p_data(new Data(data2)) {}
      
  void set_value(double value2)
  {
      *p_value = value2;
  }

  double get_value() const { return (p_data.get() == NULL) ? *p_value : *p_value / p_data->get_value(); }

  Data operator / (const Data& data2) {
    return Data(p_value, data2);
  }
private:
  shared_ptr<double> p_value;
  shared_ptr<Data> p_data;
  }; 
  

int main(int argc, char* argv[])
{
    Data ibm_price(136);
    Data ibm_earning(11647411200);
    Data ibm_shares(885600000);

    Data ibm_eps = ibm_earning/ibm_shares;
    assert(11647411200. / 885600000. == ibm_eps.get_value());
    cout<<ibm_eps.get_value()<<endl;

    Data ibm_pe = ibm_price/ibm_eps; 
    assert(136. / (11647411200. / 885600000.) == ibm_pe.get_value());
    cout<<ibm_pe.get_value()<<endl;
    
    ibm_price.set_value(68);
    assert(68. / (11647411200. / 885600000.) == ibm_pe.get_value());
    cout << ibm_pe.get_value() << endl;
}
