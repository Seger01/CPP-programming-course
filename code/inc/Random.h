#ifndef RANDOM_H
#define RANDOM_H

#include <memory>
#include <random>

class Random {
public:
    // Delete copy constructor and assignment operator to enforce singleton
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    // Static function to get the singleton instance
    static Random& getInstance() {
        static Random instance;
        return instance;
    }

    // Function to generate a random integer within a specific range [min, max]
    int generateIntInRange(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine);
    }

private:
    // Private constructor to enforce singleton pattern
    Random() : engine(std::random_device{}()) {}

    // Mersenne Twister random engine
    std::mt19937 engine;
};

// Usage example:
// int randomValue = Random::getInstance().generateIntInRange(1, 100);

#endif // RANDOM_H
