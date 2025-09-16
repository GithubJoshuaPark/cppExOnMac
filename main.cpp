#include <iostream>
#include "calculator.h" // We include our own header file using quotes

int main() {
    int num1 = 10;
    int num2 = 25;

    // The compiler now knows about addNumbers() from the header file
    int sum = addNumbers(num1, num2);

    std::cout << "The sum of " << num1 << " and " 
                               << num2 << " is: " 
			       << sum 
			       << std::endl;

    return 0;
}
