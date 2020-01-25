#include <iostream>
#include <limits.h>
#include <float.h>

using namespace std;

class Test {
        int &t;
    public:
        Test (int &t):t(t) {}
        int getT() {return t;}
};

int     main() {
    float a = 0.1;
    float b = 0.2;
    cout << a + b;
    return 0;
}