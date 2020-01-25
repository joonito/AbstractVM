#include <iostream>
#include <cstring>
using namespace std;

class String {
    private:
        char *s;
        int size;
    public:
        String(const char *str = NULL);
        ~String() {delete [] s; }
        String(const String &); //copy constructor
        void print() {
            cout << s << endl;
        }
        void change(const char *);
};

String::String(const char *str)

/*
When is copy constructor called?

1. When an object of the class is returned by value.
2. When an object of the class is passed (to a function) by value as an argument.
3. When an object is constructed based on another object of the same class.
4. When the compiler generates a temporary object.

When is user-defined copy constructor needed?
We need to define our own copy constructor only if an object has pointers or any runtime allocation of the resource like file handle, a network connection..etc.

Default constructor does only shallow copy.

Deep copy is possible only with user defined copy constructor. 

Copy constructor is called when a new object is created from an existing object, as a copy of the existing object.

Assignment operator is called when an already initialized object is assigned a new value from another existing object.

*/