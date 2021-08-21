#include <iostream>

using namespace std;

class A {
    public:
        int data;

        virtual void find_average(){}
        virtual void find_median() {}
        virtual void find_mode() {}
};

int main()
{
    cout << sizeof(A) << endl;

    return 0;
}
