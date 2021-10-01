#include <iostream>
using namespace std;

template <int n> int reversed_binary_value_recursed()
{
    return 0;
}

template <int n, bool b, bool ...digits> int reversed_binary_value_recursed()
{
    int i(0);
    if (b)
    {
        i = 1 << n;
    }
    return i + reversed_binary_value_recursed<n + 1, digits...>();
}

// Enter your code for reversed_binary_value<bool...>()
template <bool b, bool ...digits> int reversed_binary_value()
{
    return b + reversed_binary_value_recursed<1, digits...>();
}

template <int n, bool...digits>
struct CheckValues {
  	static void check(int x, int y)
  	{
    	CheckValues<n-1, 0, digits...>::check(x, y);
    	CheckValues<n-1, 1, digits...>::check(x, y);
  	}
};

template <bool...digits>
struct CheckValues<0, digits...> {
  	static void check(int x, int y)
  	{
    	int z = reversed_binary_value<digits...>();
    	std::cout << (z+64*y==x);
  	}
};

int main()
{
  	int t; std::cin >> t;

  	for (int i=0; i!=t; ++i) {
		int x, y;
    	cin >> x >> y;
    	CheckValues<6>::check(x, y);
    	cout << "\n";
  	}
}

