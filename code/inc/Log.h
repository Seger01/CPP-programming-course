#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <iostream>
#include <string>

class Log {
public:
    Log(const std::string& filename) {
        logFile.open(filename, std::ios::out | std::ios::app); // Open in append mode
        if (!logFile.is_open()) {
            std::cerr << "Error opening log file: " << filename << "\n";
        }
    }

    ~Log() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    // Overload the << operator for console output and log file
    template <typename T> Log& operator<<(const T& value) {
        std::cout << value; // Output to console
        if (logFile.is_open()) {
            logFile << value; // Write to log file
        }
        return *this; // Return current object
    }

    // Method to add a message to the log file without a newline
    void add(const std::string& message) {
        if (logFile.is_open()) {
            logFile << message; // Write to log file
        }
    }

    // Method to add a message to the log file with a newline
    void addln(const std::string& message) {
        if (logFile.is_open()) {
            logFile << message << std::endl; // Write to log file with a newline
        }
    }

private:
    std::ofstream logFile; // File stream to log output
};

#endif // LOG_H
