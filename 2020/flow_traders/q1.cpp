#include <iostream>
using namespace std;

int main()
{
    int i, &j = i;
    [=]
    {
        cout << is_same<decltype((j)), int         >::value
             << is_same<decltype((j)), int      &  >::value
             << is_same<decltype((j)), int const&  >::value
             << is_same<decltype((j)), int      && >::value
             << is_same<decltype((j)), int const&& >::value;
    }();
}
