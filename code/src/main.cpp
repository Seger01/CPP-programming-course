#include <iostream>

// #include "Object.h"
//
// // main function with input args and return type int the one input argument is a
// // file path
// int main(int argc, char* argv[]) {
//     // check if the input argument is not provided
//     if (argc < 2) {
//         // print the error message
//         std::cerr << "Usage: " << argv[0] << " FILE_PATH" << std::endl;
//         // return 1 to indicate the error
//         return 1;
//     }
//
//     // print the file path
//     std::cout << "File path: " << argv[1] << std::endl;
//
//     Object object;
//
//     object.update();
//
//     // return 0 to indicate the success
//     return 0;
// }
//

#include <cstring>
#include <iostream>

// Base class for all products
class Product {
public:
    virtual ~Product() = default;
    virtual void use() const = 0;
};

// Factory class with fixed-size array for registered products
class Factory {
public:
    using CreatorFunc = Product* (*)();

    // Maximum number of products that can be registered
    static constexpr int MAX_PRODUCTS = 10;

    // Singleton instance
    static Factory& instance() {
        static Factory factoryInstance;
        return factoryInstance;
    }

    // Registers a product type with a string ID
    bool registerProduct(const char* id, CreatorFunc creator) {
        if (m_registeredCount >= MAX_PRODUCTS)
            return false; // Array full

        m_ids[m_registeredCount] = id;
        m_creators[m_registeredCount] = creator;
        ++m_registeredCount;
        return true;
    }

    // Creates a product based on the string ID
    Product* createProduct(const char* id) const {
        for (int i = 0; i < m_registeredCount; ++i) {
            if (std::strcmp(m_ids[i], id) == 0) {
                return m_creators[i]();
            }
        }
        return nullptr;
    }

private:
    Factory() : m_registeredCount(0) {}

    // Arrays to store product IDs and creation functions
    const char* m_ids[MAX_PRODUCTS];
    CreatorFunc m_creators[MAX_PRODUCTS];
    int m_registeredCount;
};

// Self-registering derived product classes
class ProductA : public Product {
public:
    void use() const override { std::cout << "Using ProductA" << std::endl; }

    // Static function to create a new instance of ProductA
    static Product* create() { return new ProductA(); }

private:
    // Static member to register ProductA with the factory
    static const bool registered;
};

// Register ProductA in the factory
const bool ProductA::registered = Factory::instance().registerProduct("ProductA", ProductA::create);

class ProductB : public Product {
public:
    void use() const override { std::cout << "Using ProductB" << std::endl; }

    // Static function to create a new instance of ProductB
    static Product* create() { return new ProductB(); }

private:
    // Static member to register ProductB with the factory
    static const bool registered;
};

// Register ProductB in the factory
const bool ProductB::registered = Factory::instance().registerProduct("ProductB", ProductB::create);

int main() {
    // Create products using the factory
    Product* productA = Factory::instance().createProduct("ProductA");
    Product* productB = Factory::instance().createProduct("ProductB");

    if (productA) {
        productA->use();
        delete productA;
    }
    if (productB) {
        productB->use();
        delete productB;
    }

    return 0;
}
