#include <iostream>
using namespace std;

struct passengers { virtual ~passengers() {} };
struct pilots : passengers { ~pilots() {} };

struct airplane 
{
    virtual void fly(passengers *p) 
    {
        cout << "airplane::fly(passengers)" << endl;
    }

    virtual void fly(pilots *p) 
    {
        cout << "airplane::fly(pilots)" << endl;
    }
};

struct businessjet : airplane 
{
    virtual void fly(passengers *p)
    {       
        cout << "businessjet::fly(passengers)" << endl;
    }       
    
    virtual void fly(pilots *p)
    {
        cout << "businessjet::fly(pilots)" << endl;
    }
};

int main()
{
    passengers *pa = new passengers;
    passengers *pi = new pilots;
    airplane *ap = new airplane;
    airplane *bj = new businessjet;
    ap->fly(pa);
    bj->fly(pa);
    cout << "Pilots fly as passengers:" << endl;
    ap->fly(pi);
    bj->fly(pi);
    cout << "Pilots fly as pilots:" << endl;
    pilots *pil = dynamic_cast<pilots *>(pi);
    ap->fly(pil);
    bj->fly(pil);
    delete pa;
    delete pi;
    delete ap;
    delete bj;
    return 0;
}
