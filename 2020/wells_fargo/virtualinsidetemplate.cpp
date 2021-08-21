#include <iostream>
#include <string>
using namespace std;

template <class T> struct A {
     T t;
     A() { cout << "In A constructor." << endl; }
     virtual string func() { return string("A"); }
     virtual T func1() { return T("A"); }
     //template <class U> virtual U func2() { return U("A"); } // error
     template <class U> U func3() { return U("A"); }
     virtual ~A() { cout << "In A destructor." << endl; }
};

template <class T> struct B : A<T> {
     B() { cout << "In B constructor." << endl; }
     string func() override { return string("B"); }
     T func1() override { return T("B"); }
     //template <class U> U func2() override { return U("A"); } // error
     ~B() { cout << "In B destructor." << endl; }
};

int main()
{
    A<string> *a = new B<string>();
    cout << a->func() << endl;
    cout << a->func1() << endl;
    //cout << a->func2<string>() << endl; // error
    cout << a->func3<string>() << endl;
    delete a;
    return 0;
}
