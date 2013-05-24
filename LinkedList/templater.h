#ifndef template_header
#define template_header

#include <iostream>
using namespace std;

template <typename T>
class templater
{
private:
    T value1;
    T value2;

public:
    templater();
    void setValues(T value1, T value2);
    void printValues();

};
    
template <typename T>
templater <T> :: templater()
{
    value1 = T();
    value2 = T();
}

template <typename T>
void templater <T> :: setValues(T newvalue1, T newvalue2)
{
    value1 = newvalue1;
    value2 = newvalue2;
}

template <typename T>
void templater <T> :: printValues()
{
    cout << value1 << value2 << endl;
}

#endif
