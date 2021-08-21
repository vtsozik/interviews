#include <iostream>
#include <string>
using namespace std;

struct car 
{
    virtual string drive() { return string("car::drive"); }
    virtual string fillup() { return string("car::fillup"); }
};

struct ford : car
{
    virtual string drive() { return string("ford::drive"); }
    virtual string fillup() { return string("ford::fillup"); }
};

struct eleccar : car
{
    virtual string drive() { return string("eleccar::drive"); }
    virtual string charge() { return string("eleccar::charge"); }
};

struct tesla : eleccar
{
    virtual string drive() { return string("tesla::drive"); }
    virtual string charge() { return string("tesla::charge"); }
};

int main()
{
    car* fc = new ford;
    car* tc = new tesla;
    eleccar* tec = dynamic_cast<eleccar *>(tc);
    cout << "Calling fc->drive(): " << fc->drive() << endl;
    cout << "Calling fc->fillup(): " << fc->fillup() << endl;
    cout << "Calling tc->drive(): " << tc->drive() << endl;
    cout << "Calling tc->fillup(): " << tc->fillup() << endl;
    cout << "Cannot call tc->charge(); " << endl;
    cout << "Calling tec->charge(): " << tec->charge() << endl;
    delete fc;
    delete tc;
    return 0;
}
