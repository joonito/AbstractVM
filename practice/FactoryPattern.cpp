#include <iostream>
using namespace std;

enum VehicleType { 
    VT_TwoWheeler,    VT_ThreeWheeler,    VT_FourWheeler 
};

class Vehicle {
    public:
        virtual void printVehicle() = 0;
        static Vehicle* Create(VehicleType type);
};

class TwoWheeler : public Vehicle { 
public: 
    void printVehicle() { 
        cout << "I am two wheeler" << endl; 
    } 
}; 
class ThreeWheeler : public Vehicle { 
public: 
    void printVehicle() { 
        cout << "I am three wheeler" << endl; 
    } 
}; 
class FourWheeler : public Vehicle { 
    public: 
    void printVehicle() { 
        cout << "I am four wheeler" << endl; 
    } 
}; 

Vehicle* Vehicle::Create(VehicleType type) { 
    if (type == VT_TwoWheeler) 
        return new TwoWheeler(); 
    else if (type == VT_ThreeWheeler) 
        return new ThreeWheeler(); 
    else if (type == VT_FourWheeler) 
        return new FourWheeler(); 
    else return NULL; 
} 

