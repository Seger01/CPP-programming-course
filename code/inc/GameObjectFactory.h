#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <cstring>

#include "GameObject.h"

// Factory class with fixed-size array for registered products
class GameObjectFactory {
public:
    using CreatorFunc = GameObject* (*)();

    // Singleton instance
    static GameObjectFactory& instance();

    // Registers a product type with a string ID
    bool registerProduct(const char* id, CreatorFunc creator);
    // Creates a product based on the string ID
    GameObject* createProduct(const char* id) const;
    GameObject* createProduct(const char* id, const char* name, const char* description, int min = 0, int max = 0,
                              int protection = 0) const;

private:
    GameObjectFactory() : m_registeredCount(0) {}

    // Maximum number of products that can be registered
    static constexpr int MAX_PRODUCTS = 10;

    // Arrays to store product IDs and creation functions
    const char* m_ids[MAX_PRODUCTS];
    CreatorFunc m_creators[MAX_PRODUCTS];
    int m_registeredCount;
};

#endif // GAMEOBJECTFACTORY_H
