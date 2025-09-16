#include <iostream>

// Function declaration (also called a prototype)
int addNumbers(int a, int b);

int main() {
    int num1 = 10;
    int num2 = 25;

    // Call the function and store the returned value
    int sum = addNumbers(num1, num2);

    std::cout << "The sum of " 
              << num1 
	      << " and " 
	      << num2 
	      << " is: " 
	      << sum 
	      << std::endl;

    return 0;
}

// Function definition
int addNumbers(int a, int b) {
    int result = a + b;
    return result;
}
