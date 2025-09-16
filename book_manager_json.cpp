#include <iostream>
#include <string>
#include <fstream> // Required for file operations
#include "json.hpp" // JSON 라이브러리 헤더 파일 포함

// Define the Book class
class Book {
    public:
        std::string title;
	    std::string author;

	    int year;

	    void setDetail(std::string t, std::string a, int y){
            title = t;
            author = a;
            year = y;
	    }

        void printDetail(){
           std::cout << "Title : " << title  << std::endl;
           std::cout << "Author: " << author << std::endl;
           std::cout << "Year  : " << year   << std::endl;
           std::cout << "-------------------------------" << std::endl;
        }
};

int main() {
    int numBook;
    std::cout << "How many books would you like to enter?";
    std::cin  >>  numBook;

    // --- New: Input Validation ---
    if (numBook < 1) {
        std::cout << "Error: The number of books must be at least 1." << std::endl;
        return 1; // Exit with an error code
    }

    // Skip the newline character left in the input buffer
    std::cin.ignore();

    // Dynamically create an array of Book objects on the heap
    Book* bookCollection = new Book[numBook];

    // Loop to get input for for each book
    for(int i = 0; i < numBook; ++i){
        std::string tempTitle, tempAuthor;
        int tempYear;

        std::cout << "\nEntering details for book #" << i + 1 << ":" << std::endl;
        std::cout << "Enter Title: ";
        std::getline(std::cin, tempTitle);

        std::cout << "Enter author: ";
        std::getline(std::cin, tempAuthor);

        std::cout << "Enter year: ";
        std::cin >> tempYear;
        std::cin.ignore(); // Clear the input buffer again

        // Assign the entered values to the current object in the array
        bookCollection[i].setDetail(tempTitle, tempAuthor, tempYear);
    }

    // --- JSON 객체 생성 및 데이터 저장 ---
    nlohmann::json jsonArray; // JSON 배열 객체 생성

    // 루프를 돌며 각 Book 객체를 JSON 객체로 변환
    for (int i = 0; i < numBook; ++i) {
        nlohmann::json jsonBook; // JSON 객체 생성

        jsonBook["title"] = bookCollection[i].title;
        jsonBook["author"] = bookCollection[i].author;
        jsonBook["year"] = bookCollection[i].year;

        jsonArray.push_back(jsonBook); // JSON 배열에 객체 추가
    }

    // --- New: File Handling ---
    std::ofstream outFile("book.json"); 

    if (!outFile.is_open()) {
        std::cout << "Error: Could not open the file book.json" << std::endl;
        return 1;
    }

    std::cout << "\n--- Your Book Collection ---" << std::endl;
    outFile << "-------------------------------------" << std::endl;

    // Loop to print the details of all books
    for (int i = 0; i < numBook; ++i) {
        bookCollection[i].printDetail();

        // --- New: Write to file ---
        outFile << "Title : " << bookCollection[i].title   << std::endl;
        outFile << "Author: " << bookCollection[i].author  << std::endl;
        outFile << "Year  : " << bookCollection[i].year    << std::endl;
        outFile << "-------------------------------------" << std::endl;
    }
    
    // JSON을 파일에 쓰기 (dump(4)는 가독성을 위해 4칸 들여쓰기)
    outFile << jsonArray.dump(4);
    
    // --- New: Close the file ---
    outFile.close();

    // Free the dynamically allocated memory
    delete[] bookCollection;

    std::cout << "Data has been saved to book.txt" << std::endl;

    return 0;
}
