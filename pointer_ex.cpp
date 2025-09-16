#include <iostream>

int main(){
   int myVariable = 25;
   int *myPointer;

   myPointer = &myVariable;

   std::cout << "Value of myVariable            : " << myVariable << std::endl;

   // print the memory address of myVariable
   std::cout << "Address of myVariable          : " << myPointer << std::endl;

   // print the value stored in the pointer (the address of myVariable)
   std::cout << "Value of myPointer(the address): "<< myPointer << std::endl;

   // Print the value the pointer is pointing to
   std::cout << "Value pointed to by myPointer  : " << *myPointer << std::endl;

   // Change the value of myVariable using the pointer
   *myPointer = 50;

   // Now print the new value of myVariable
   std::cout << "New value of myVariable        : "<< myVariable << std::endl;

   return 0;
}
