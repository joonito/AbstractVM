#include <iostream>

class demo : public std::exception {
};

int     main() {
    try {
        throw demo();
    }
    catch (demo d) {
        cout << "Caught exception of demo class \n";
    }
}