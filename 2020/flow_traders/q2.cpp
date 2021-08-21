#include <iostream>
using namespace std;

int main()
{
    int a = 0;
    decltype((a)) b = a;
    b++;
    std::cout << a << b;
}
