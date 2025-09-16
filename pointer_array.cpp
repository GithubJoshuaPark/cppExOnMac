#include <iostream>
#include <iomanip> // Include the header for stream manipulators

int main() {
    // Declare and initialize an array
    int numbers[5] = {100, 200, 300, 400, 500};

    // The array name 'numbers' itself is a pointer to the first element
    // Let's create a pointer and assign the array's address to it
    int* ptr = numbers; // No & operator needed here!
    int arraySize = sizeof(numbers)/sizeof(numbers[0]);


    std::cout << "The size of Array : "<< arraySize << std::endl;	

    // Print the address of each element
    for(int i = 0; i< arraySize; i++){
	//std::cout << "Address of numbers[" << i << "]: " << ptr+i << std::endl; 
	
	std::cout << "Address of numbers[" << i << "]: "
                  << std::hex 
		  << std::setfill('0') 
		  << std::setw(16) 
		  << (long long)(ptr + i) 
		  << std::endl;

	//std::cout << "Value   of numbers[" << i << "]: " << *(ptr+i) << std::endl;
	std::cout << "Value    of numbers[" << i << "]: " 
	          << std::dec 
		  << *(ptr + i) 
		  << std::endl;
    }	

    return 0;
}

