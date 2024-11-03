#include "String.h"

String::String() : data(nullptr), size(0) {} // Initialize data to nullptr and size to 0

String::String(const char* str) {
    allocateAndCopy(str); // Allocate and copy string
}

String::String(const String& other) {
    allocateAndCopy(other.data); // Allocate and copy string from other
}

String& String::operator=(const String& other) {
    if (this != &other) {            // Avoid self-assignment
        freeMemory();                // Free existing memory
        allocateAndCopy(other.data); // Allocate and copy from other
    }
    return *this;
}

String::~String() {
    freeMemory(); // Free memory in the destructor
}

void String::allocateAndCopy(const char* str) {
    if (str) {                     // Only allocate if str is not null
        size = std::strlen(str);   // Get the length of the string
        data = new char[size + 1]; // Allocate memory (+1 for null terminator)
        std::strcpy(data, str);    // Copy the string
    } else {
        data = nullptr; // If str is null, set data to nullptr
        size = 0;       // Set size to 0
    }
}

void String::freeMemory() {
    if (data != nullptr) { // Check if data is not nullptr before deleting
        delete[] data;     // Free the allocated memory
        data = nullptr;    // Prevent dangling pointer by resetting to nullptr
    }
}

const char* String::c_str() const {
    return data ? data : ""; // Return C-style string
}

size_t String::length() const {
    return size; // Return the size of the string
}

String String::getFirstWord() const {
    if (!data) {
        return String(""); // Return an empty String if data is null
    }

    // Find the position of the first space character or end of string
    size_t firstSpacePos = 0;
    while (firstSpacePos < size && data[firstSpacePos] != ' ') {
        ++firstSpacePos;
    }

    // Create a new String from the first word
    char* firstWord = new char[firstSpacePos + 1];
    std::strncpy(firstWord, data, firstSpacePos);
    firstWord[firstSpacePos] = '\0';

    String result(firstWord);
    delete[] firstWord;
    return result;
}

void String::removeFirstWord() {
    if (!data || size == 0) {
        return; // If data is null or empty, there's nothing to remove
    }

    // Find the position of the first space character
    size_t firstSpacePos = 0;
    while (firstSpacePos < size && data[firstSpacePos] != ' ') {
        ++firstSpacePos;
    }

    // If the entire string is a single word (no spaces), clear the string
    if (firstSpacePos == size) {
        freeMemory();
        size = 0;
        data = new char[1];
        data[0] = '\0';
        return;
    }

    // Find the first non-space character after the first word
    size_t newStartPos = firstSpacePos;
    while (newStartPos < size && data[newStartPos] == ' ') {
        ++newStartPos;
    }

    // Calculate new size after removing the first word and spaces
    size_t newSize = size - newStartPos;

    // Create a new array to hold the remaining string
    char* newData = new char[newSize + 1];
    std::strcpy(newData, data + newStartPos);

    // Free old data and update with new data
    freeMemory();
    data = newData;
    size = newSize;
}

bool String::empty() const {
    return size == 0; // Check if the size is 0
}

// Overload the << operator for String
std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.c_str(); // Output the C-style string
    return os;
}

bool String::operator==(const String& other) const {
    // Compare the lengths first, then compare the data
    return (size == other.size) && (std::strcmp(data, other.data) == 0);
}

bool String::operator==(const char* other) const {
    // Handle nullptr case if other is null
    if (!other) {
        return data == nullptr;
    }
    // Compare this string's data with the C-style string
    return std::strcmp(data, other) == 0;
}

void String::append(const String& other) {
    // Call the append function with the other string's data
    append(other.data);
}

void String::append(const char* str) {
    if (!str || str[0] == '\0') {
        return; // Nothing to append if str is null or empty
    }

    size_t strLength = std::strlen(str);
    size_t newSize = size + strLength;

    // Allocate new memory to hold the combined string
    char* newData = new char[newSize + 1]; // +1 for the null terminator

    // Copy existing data to newData
    if (data) {
        std::strcpy(newData, data);
    }

    // Concatenate the new string
    std::strcpy(newData + size, str); // Start writing after the existing data

    // Free old memory and update data and size
    freeMemory();
    data = newData;
    size = newSize;
}
