
/*
try: represents a block of code that can throw an exception.

catch: represents a block of code that is executed when a particular exception is thrown.

throw: Used to throw an exception. Also used to list the exceptions that a function throws, but doesn’t handle itself.

Why Exception Handling?

1) Separation of Error Handling code from Normal Code: In traditional error handling codes, 
there are always if else conditions to handle errors. 
These conditions and the code to handle errors get mixed up with the normal flow. 
This makes the code less readable and maintainable. 
With try catch blocks, the code for error handling becomes separate from the normal flow.

*/

#include <iostream> 
using namespace std; 
  
int main() 
{ 
    try { 
        try  { 
            throw 20; 
        } 
        catch (int n) { 
             cout << "Handle Partially "; 
             throw n;   //Re-throwing an exception 
        } 
    } 
    catch (int n) { 
        cout << "Handle remaining "; 
    } 
    return 0; 
}