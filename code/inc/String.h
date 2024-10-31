#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstring>
#include <iostream>

class String {
public:
    String();                               // Default constructor
    String(const char* str);                // Constructor from C-style string
    String(const String& other);            // Copy constructor
    String& operator=(const String& other); // Copy assignment operator
    ~String();                              // Destructor

    const char* c_str() const; // Get C-style string
    size_t length() const;     // Get the length of the string
    String getFirstWord() const;
    void removeFirstWord();

    bool empty() const; // Check if the string is empty

    // Friend function to overload the << operator
    friend std::ostream& operator<<(std::ostream& os, const String& str);
    bool operator==(const String& other) const; // Compare with another String
    bool operator==(const char* other) const;   // Compare with a C-style string

private:
    char* data;  // Pointer to dynamically allocated string
    size_t size; // Length of the string

    void allocateAndCopy(const char* str); // Helper to allocate and copy string
    void freeMemory();                     // Helper to free memory
};

#endif // STRING_H
