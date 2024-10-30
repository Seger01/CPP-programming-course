#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstring>
#include <iostream>

class MyString {
public:
    MyString();                                 // Default constructor
    MyString(const char* str);                  // Constructor from C-style string
    MyString(const MyString& other);            // Copy constructor
    MyString& operator=(const MyString& other); // Copy assignment operator
    ~MyString();                                // Destructor

    const char* c_str() const; // Get C-style string
    size_t length() const;     // Get the length of the string

    // Friend function to overload the << operator
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);

private:
    char* data;  // Pointer to dynamically allocated string
    size_t size; // Length of the string

    void allocateAndCopy(const char* str); // Helper to allocate and copy string
    void freeMemory();                     // Helper to free memory
};

#endif // STRING_H
