#include <iostream>
#include <string.h>
using namespace std;

class mystring 
{
   char *m_storage;
   size_t m_length;
public:
   mystring(const char *c) : m_storage(nullptr), m_length(0)
   {
#ifdef DEBUG
       cout << "DEBUG: in mystring(char *c) constructor." << endl;
#endif
       if (c != nullptr)
       {
	   m_length = strlen(c);
           m_storage = new char[m_length + 1];
           strncpy(m_storage, c, m_length);
       }
   }

   mystring(const mystring& other) : mystring(other.m_storage)
   { 
#ifdef DEBUG
       cout << "DEBUG: in mystring(const mystring& other) constructor." << endl;
#endif
   }

   mystring& operator=(const mystring& other)
   {
#ifdef DEBUG
       cout << "DEBUG: in mystring& operator=(const mystring& other) assignment operator." << endl;
#endif
       if (this != &other)
       {
           mystring t(other);
           this->~mystring();
	   this->operator=(std::move(t));
       }
       return *this;
   }

   virtual ~mystring()
   {
#ifdef DEBUG
       cout << "DEBUG: in ~mystring() destructor." << endl;
#endif
       if (m_storage != nullptr)
       {
           delete[] m_storage;
	   m_storage = nullptr;
           m_length = 0;
       }
   }

   void print()
   {
       cout << m_storage << endl;
   }

   // MOVE
   
   mystring(mystring&& other) noexcept : m_storage(other.m_storage), m_length(other.m_length)
   {
#ifdef DEBUG
       cout << "DEBUG: in mystring(const mystring&& other) move constructor." << endl;
#endif
       other.m_storage = nullptr;
       other.m_length = 0;
   }

   mystring& operator=(mystring&& other) noexcept
   {
#ifdef DEBUG
       cout << "DEBUG: in mystring& operator=(const mystring&& other) move assignment operator." << endl;
#endif
       if (this != &other)
       {
	   this->~mystring();
	   m_storage = other.m_storage;
           m_length = other.m_length;
           other.m_storage = nullptr;
           other.m_length = 0;
       }
       return *this; 
   }
};

mystring makemystring()
{
    mystring mystr("Observe move copy constructor is called above.");
    return std::move(mystr); // Use std::move to disable NRVO.
}

int main()
{
    const char *c = "Observe constructor called constructor above.";
    mystring s(c);
    mystring s1(s);
    s.print();
    const char *c1 = "Observe move assignament operator is called above.";
    mystring s2(c1);
    s1 = s2;
    s1.print();
    mystring s3 = makemystring();
    s3.print();
    return 0;
}	
