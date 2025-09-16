#include <iostream>
#include <string>

// Define the Car class
class Car {
public:
    // Member variables (attributes)
    int year;
    std::string color;

    // Member function (behavior)
    void honk() {
        std::cout << "Beep beep!" << std::endl;
    }
};

int main() {
    // Create an object (an instance of the Car class)
    Car myCar;

    // Access and assign values to member variables
    myCar.year = 2023;
    myCar.color = "blue";

    // Call the member function
    std::cout << "My car is a " 
              << myCar.color 
              << " " 
              << myCar.year 
              << " model." 
              << std::endl;

    myCar.honk();

    return 0;
}
