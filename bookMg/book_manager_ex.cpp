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
    // 1. 파일을 읽기 위해 ifstream 객체를 생성합니다.
    std::ifstream inFile(FILE_NAME);
    json j; // 2. JSON 데이터를 담을 객체를 생성합니다.

    // 3. 파일이 성공적으로 열렸는지 확인합니다.
    if (inFile.is_open()) {
        try {
            // 4. 파일의 내용을 JSON 객체 'j'로 파싱(parsing)합니다.
            inFile >> j;
        } catch (const json::parse_error& e) {
            // 5. 만약 파일 내용이 올바른 JSON 형식이 아닐 경우 예외를 처리합니다.
            std::cout << "Warning: Could not parse JSON file. Starting with an empty list." << std::endl;
            j = json::array(); // 빈 배열로 초기화합니다.
        }
    } else {
        // 6. 파일이 존재하지 않을 경우, 경고 메시지를 출력하고 새롭게 시작합니다.
        std::cout << "Warning: " << FILE_NAME << " not found. Creating a new one." << std::endl;
        j = json::array();
    }
    // 7. 파싱된 JSON 객체 또는 빈 배열 객체를 반환합니다.
    return j;
}

// JSON 데이터를 파일에 쓰는 함수
void writeJsonToFile(const json& j) {
    // 1. 파일을 쓰기 위해 ofstream 객체를 생성합니다.
    std::ofstream outFile(FILE_NAME);

    // 2. 파일이 성공적으로 열렸는지 확인합니다.
    if (!outFile.is_open()) {
        std::cout << "Error: Could not open " << FILE_NAME << " for writing." << std::endl;
        return;
    }

    // 3. JSON 객체를 문자열로 변환하여 파일에 씁니다.
    // json 객체 j의 내용을 문자열 형태로 변환(serialize)합니다. 
    // j.dump(4): 인자로 4를 전달하면, 
    // JSON 구조를 사람이 읽기 쉽게 4칸씩 들여쓰기(pretty-printing)하여 변환해 줍니다.
    outFile << j.dump(4);

    // 4. 파일을 닫습니다.
    outFile.close();
    std::cout << "Data saved successfully to " << FILE_NAME << "." << std::endl;
}

// 입력 버퍼를 안전하게 비우는 헬퍼 함수
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        std::cout << "Title : " << bookList[i]["title"].get<std::string>() << std::endl;
        std::cout << "Author: " << bookList[i]["author"].get<std::string>() << std::endl;
        std::cout << "Year  : " << bookList[i]["year"].get<int>() << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
}

// 2. 책 추가 함수
void enterBooks(json& bookList) {
    int numBooks;
    std::cout << "How many books would you like to enter? ";
    std::cin >> numBooks;

    if (numBooks < 1) {
        std::cout << "The number of books must be at least 1." << std::endl;
        return;
    }

    clearInputBuffer(); // 입력 버퍼 비우기

    for (int i = 0; i < numBooks; ++i) {
        std::string title, author;
        int year;

        std::cout << "\nEntering details for book #" << i + 1 << ":" << std::endl;
        std::cout << "Enter title: ";
        std::getline(std::cin, title);

        std::cout << "Enter author: ";
        std::getline(std::cin, author);

        std::cout << "Enter year: ";
        std::cin >> year;
        clearInputBuffer();

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
        clearInputBuffer();
        std::cout << "Invalid input. Please enter a valid number from the list." << std::endl;
        return;
    }

    bookList.erase(index - 1);
    std::cout << "Book at index " << index << " has been removed." << std::endl;
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

    if (std::cin.fail() || index < 1 || index > static_cast<int>(bookList.size())) {
        std::cin.clear();
        clearInputBuffer();
        std::cout << "Invalid input. Please enter a valid number from the list." << std::endl;
        return;
    }

    clearInputBuffer();

    std::string newTitle, newAuthor;
    int newYear;

    std::cout << "Enter new title: ";
    std::getline(std::cin, newTitle);

    std::cout << "Enter new author: ";
    std::getline(std::cin, newAuthor);

    std::cout << "Enter new year: ";
    std::cin >> newYear;
    clearInputBuffer();

    bookList[index - 1]["title"] = newTitle;
    bookList[index - 1]["author"] = newAuthor;
    bookList[index - 1]["year"] = newYear;

    std::cout << "Book at index " << index << " has been updated." << std::endl;
    writeJsonToFile(bookList);
}

int main() {
    json bookList = readJsonFromFile(); // 프로그램 시작 시 파일에서 데이터 읽어오기

    int choice;
    do {
        std::cout << "\n--- Book Management System ---" << std::endl;
        std::cout << "1. List All Books"  << std::endl;
        std::cout << "2. Enter New Books" << std::endl;
        std::cout << "3. Remove a Book"   << std::endl;
        std::cout << "4. Update a Book"   << std::endl;
        std::cout << "5. Exit"            << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            clearInputBuffer();
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
                std::cout << "Invalid choice. Please enter a number from 1 to 5." << std::endl;
                break;
        }

    } while (choice != 5);

    return 0;
}