#include <iostream>
#include "lib.hpp"
using namespace std;

A::A() { cout << "default ctor" << endl; }
A::~A() { cout << "dctor" << endl; }
void A::f(int i/* = 0*/) { cout << "f(int i = 0)" << endl; this->i = i; }
