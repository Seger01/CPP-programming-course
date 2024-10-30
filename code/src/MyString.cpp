#include "MyString.h"

MyString::MyString() : data(nullptr), size(0) {} // Initialize data to nullptr and size to 0

MyString::MyString(const char* str) {
    allocateAndCopy(str); // Allocate and copy string
}

MyString::MyString(const MyString& other) {
    allocateAndCopy(other.data); // Allocate and copy string from other
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {            // Avoid self-assignment
        freeMemory();                // Free existing memory
        allocateAndCopy(other.data); // Allocate and copy from other
    }
    return *this;
}

MyString::~MyString() {
    freeMemory(); // Free memory in the destructor
}

void MyString::allocateAndCopy(const char* str) {
    if (str) {                     // Only allocate if str is not null
        size = std::strlen(str);   // Get the length of the string
        data = new char[size + 1]; // Allocate memory (+1 for null terminator)
        std::strcpy(data, str);    // Copy the string
    } else {
        data = nullptr; // If str is null, set data to nullptr
        size = 0;       // Set size to 0
    }
}

void MyString::freeMemory() {
    if (data != nullptr && size > 0) { // Check if data is not nullptr before deleting
        delete[] data;                 // Free the allocated memory
        data = nullptr;                // Prevent dangling pointer by resetting to nullptr
    }
}

const char* MyString::c_str() const {
    return data ? data : ""; // Return C-style string
}

size_t MyString::length() const {
    return size; // Return the size of the string
}

// Overload the << operator for String
std::ostream& operator<<(std::ostream& os, const MyString& str) {
    std::cout << "overloaded operator" << std::endl;
    std::cout << str.size << std::endl;

    os << str.c_str(); // Output the C-style string
    return os;
}
