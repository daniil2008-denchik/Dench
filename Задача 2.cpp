#include <iostream>
#include <string>
using namespace std;


class Vehicle {
protected:
    int speed;     
    int weight;    
    
public:
    
    Vehicle(int spd, int wgt) : speed(spd), weight(wgt) {}
    
    
    void display() {
        cout << "Transport: skorosti " << speed << " km/h, ves " << weight << " kg";
    }
    
    
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
private:
    string brand;
    int doors;
    
public:
    
    Car(int spd, int wgt, string br, int d) : Vehicle(spd, wgt), brand(br), doors(d) {}
    
    
    void display() {
        Vehicle::display();  
        cout << ", marka: " << brand << ", doors: " << doors;
    }
};


class Bicycle : public Vehicle {
private:
    string type;
    
public:
    
    Bicycle(int spd, int wgt, string tp) : Vehicle(spd, wgt), type(tp) {}
    
    
    void display() {
        Vehicle::display();  
        cout << ", tip: " << type;
    }
};

int main() {
    
    Car car(180, 1500, "Toyota Camry", 4);
    Bicycle bike(25, 12, "mountain");
    Vehicle vehicle(60, 800);
    
    cout << "=== Call display() on each object ===" << endl;
    
    cout << "\n1. Base class Vehicle:" << endl;
    vehicle.display();
    
    cout << "\n\n2. Car class (successor):" << endl;
    car.display();
    
    cout << "\n\n3. Class Bicycle (successor):" << endl;
    bike.display();
    
    cout << "\n\n=== Further demonstration of polymorphism ===" << endl;
    cout << "Via a pointer to a base class:" << endl;
    
    Vehicle* vehicles[2];
    vehicles[0] = &car;
    vehicles[1] = &bike;
    
    for (int i = 0; i < 2; i++) {
        cout << "Element " << i + 1 << ": ";
        vehicles[i]->display();
        cout << endl;
    }
    
    return 0;
}
