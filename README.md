# Exercising C++ (console-based)

I want to modify the current source code.
It should show menu list when it start.
1. List Book List
2. Enter Book List
	-> How many book would you like to enter?
3. Remove a book
4. Update a book

5. **메뉴 기반 인터페이스:** `do-while` 루프와 `switch` 구문을 사용하여 사용자 선택에 따라 다른 작업을 수행합니다.
    
6. **파일 입출력 로직 변경:** JSON 파일에 데이터를 `추가(append)`하기 위해서는, 먼저 **파일의 기존 내용을 모두 읽어 메모리에 로드**해야 합니다. 그 후, 메모리에 있는 JSON 객체를 수정한 뒤, **수정된 전체 내용을 파일에 덮어쓰기**해야 합니다. JSON 형식은 텍스트 파일처럼 단순히 마지막에 내용을 덧붙이는(append) 방식이 불가능하기 때문입니다.
    
7. **기능별 함수 분리:** 코드의 가독성을 높이고 유지보수를 쉽게 하기 위해, 각 메뉴 기능을 별도의 함수로 분리합니다.

```c++

#include <iostream>
#include <string>
#include <fstream>
#include <limits> // std::numeric_limits를 사용하기 위함
#include "json.hpp" // JSON 라이브러리 헤더 파일 포함

// JSON 객체를 사용하기 위한 using 선언
using json = nlohmann::json;

// 파일명 상수
const std::string FILE_NAME = "books.json";

// 파일에서 JSON 데이터를 읽어와 반환하는 함수
json readJsonFromFile() {
    std::ifstream inFile(FILE_NAME);
    json j;
    if (inFile.is_open()) {
        try {
            inFile >> j;
        } catch (const json::parse_error& e) {
            std::cout 
             << "Warning: Could not parse JSON file."
             << "Starting with an empty list." 
             << std::endl;
            
            j = json::array();
        }
    } else {
        std::cout << "Warning: " 
                  << FILE_NAME 
                  << " not found. Creating a new one." << std::endl;
        j = json::array();
    }
    return j;
}

// JSON 데이터를 파일에 쓰는 함수
void writeJsonToFile(const json& j) {
    std::ofstream outFile(FILE_NAME);
    if (!outFile.is_open()) {
        std::cout << "Error: Could not open " 
                  << FILE_NAME 
                  << " for writing." << std::endl;
        return;
    }
    outFile << j.dump(4);
    outFile.close();
    std::cout << "Data saved successfully to " 
              << FILE_NAME 
              << "." << std::endl;
}

// 1. 책 목록 출력 함수
void listBooks(const json& bookList) {
    if (bookList.empty()) {
        std::cout << "The book list is empty." << std::endl;
        return;
    }
    std::cout << "\n--- Current Book List ---" << std::endl;
    for (size_t i = 0; i < bookList.size(); ++i) {
        std::cout << "[" << i + 1 << "] ";
        std::cout << "Title: " 
                  << bookList[i]["title"].get<std::string>()
                  << ", Author: " 
                  << bookList[i]["author"].get<std::string>()
                  << ", Year: " 
                  << bookList[i]["year"].get<int>() << std::endl;
    }
}

// 2. 책 추가 함수
void enterBooks(json& bookList) {
    int numBooks;
    std::cout << "How many books would you like to enter? ";
    std::cin >> numBooks;

    if (numBooks < 1) {
        std::cout << "The number of books must be at least 1." 
                  << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 입력 버퍼 비우기

    for (int i = 0; i < numBooks; ++i) {
        std::string title, author;
        int year;

        std::cout << "\nEntering details for book #" 
                  << i + 1 << ":" << std::endl;
        std::cout << "Enter title: ";
        std::getline(std::cin, title);

        std::cout << "Enter author: ";
        std::getline(std::cin, author);

        std::cout << "Enter year: ";
        std::cin >> year;
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );

        json newBook;
        newBook["title"] = title;
        newBook["author"] = author;
        newBook["year"] = year;
        bookList.push_back(newBook);
    }
    writeJsonToFile(bookList);
}

// 3. 책 제거 함수
void removeBook(json& bookList) {
    listBooks(bookList);
    if (bookList.empty()) {
        return;
    }

    int index;
    std::cout << "\nEnter the number of the book to remove: ";
    std::cin >> index;

    if (std::cin.fail() || index < 1 || index > static_cast<int>(bookList.size())) {
        std::cin.clear();
        
        std::cin.ignore(
             std::numeric_limits<std::streamsize>::max(), '\n'
        );
        
        std::cout << "Invalid input."
                  << "Please enter a valid number from the list." 
                  << std::endl;
        return;
    }

    bookList.erase(index - 1);
    std::cout << "Book at index " 
              << index << " has been removed." << std::endl;
    writeJsonToFile(bookList);
}

// 4. 책 업데이트 함수
void updateBook(json& bookList) {
    listBooks(bookList);
    if (bookList.empty()) {
        return;
    }

    int index;
    std::cout << "\nEnter the number of the book to update: ";
    std::cin >> index;

    if (std::cin.fail() || 
        index < 1       || 
        index > static_cast<int>(bookList.size())) 
    {
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
        std::cout << "Invalid input."
                  << "Please enter a valid number from the list." 
                  << std::endl;
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string newTitle, newAuthor;
    int newYear;

    std::cout << "Enter new title: ";
    std::getline(std::cin, newTitle);

    std::cout << "Enter new author: ";
    std::getline(std::cin, newAuthor);

    std::cout << "Enter new year: ";
    std::cin >> newYear;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bookList[index - 1]["title"] = newTitle;
    bookList[index - 1]["author"] = newAuthor;
    bookList[index - 1]["year"] = newYear;

    std::cout << "Book at index " 
              << index << " has been updated." << std::endl;
    writeJsonToFile(bookList);
}

int main() {
    // 프로그램 시작 시 파일에서 데이터 읽어오기
    json bookList = readJsonFromFile(); 

    int choice;
    do {
        std::cout << "\n--- Book Management System ---" << std::endl;
        std::cout << "1. List All Books" << std::endl;
        std::cout << "2. Enter New Books" << std::endl;
        std::cout << "3. Remove a Book" << std::endl;
        std::cout << "4. Update a Book" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            
            std::cin.ignore(
	            std::numeric_limits<std::streamsize>::max(), '\n'
	        );
	        
            choice = 0; // 유효하지 않은 입력 처리
        }

        switch (choice) {
            case 1:
                listBooks(bookList);
                break;
            case 2:
                enterBooks(bookList);
                break;
            case 3:
                removeBook(bookList);
                break;
            case 4:
                updateBook(bookList);
                break;
            case 5:
                std::cout << "Exiting program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice."
                          << "Please enter a number from 1 to 5." 
                          << std::endl;
                break;
        }

    } while (choice != 5);

    return 0;
}
```