#include <iostream>

struct A
{
    A()
    {
        throw 2;
    }
};

struct B
{
    B()
        try 
        {
            A a;
        }
        catch (int i) 
        {
            std::cout << i;
        }
};

int main() 
{
    B b;
    std::cout << 3;
    return 0;
}
