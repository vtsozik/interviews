/* Renan and Andrei asked to sketch an implementation of std::optional
 * that will not allocate any dynamic memory.
 */

#include <new>
#include <string.h>
#include <cassert>

template <class T> class myoptional {
    T *m_pt;
    char m_buff[sizeof(T)];
public:
    myoptional() : m_pt(nullptr) {}
    myoptional(const T& t) 
    {
        m_pt = new(m_buff) T(t);  
    }
    myoptional(const myoptional& myop)
    {
        m_pt = new(m_buff) T(*myop.m_pt);
    }
    myoptional& operator=(const myoptional& myop)
    {
        if (this != &myop)
	{
            m_pt = reinterpret_cast<T*>(m_buff);
	    memcpy(m_pt, myop.m_pt, sizeof(T));
	}
	return *this;
    }
    bool operator==(const T& t)
    {
        return (this->m_pt == &t || memcmp(m_pt, &t, sizeof(T)) == 0);
    }
    bool operator==(const myoptional& myop)
    {
        return this->operator==(*myop.m_pt);
    }
    operator bool() const
    {
       return m_pt != nullptr; 
    }
};

class BadBoy {
    int m_i;
public:
    BadBoy() = delete;
    BadBoy(const BadBoy& bb) : m_i(bb.m_i) {}
    BadBoy(const int& i) : m_i(i) {}
};

int main()
{
    myoptional<BadBoy> mo1;
    assert(!mo1);
    mo1 = BadBoy(3);
    assert(mo1);
    assert(mo1 == BadBoy(3));
    myoptional<BadBoy> mo2(BadBoy(4));
    assert(!(mo1 == mo2));
    return 0;
}
