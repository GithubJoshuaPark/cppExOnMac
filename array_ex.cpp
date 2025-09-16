#include <iostream>

int main() {
    // Declare and initialize an array of integers
    int numbers[5] = {10, 20, 30, 40, 50};

    // Print the elements of the array
    std::cout << "The elements of the array are:" << std::endl;

    // Loop through the array and print each element
    for (int i = 0; i < 5; ++i) {
        std::cout << "Element at index " 
	          << i 
		  << ": " 
		  << numbers[i] 
		  << std::endl;
    }

    return 0;
}
