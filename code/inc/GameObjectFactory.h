#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <cstring>

#include "GameObject.h"
#include "String.h"
#include "Vector.h"

// Factory class with fixed-size array for registered products
class GameObjectFactory {
public:
    using CreatorFunc = GameObject* (*)();

    // Singleton instance
    static GameObjectFactory& instance();

    // Registers a product type with a string ID
    bool registerObject(String id, CreatorFunc creator);

    // Creates a product based on the string ID
    GameObject* createObject(String id, String objectName);

private:
    int objectNameSeen(String objectName);
    void increaseObjectNameSeen(String objectName);
    GameObjectFactory() : m_registeredCount(0) {}

    Vector<String> m_ids;
    Vector<CreatorFunc> m_creators;

    Vector<String> objectNames;
    Vector<int> objectNameAmounts;

    int m_registeredCount;
};

#endif // GAMEOBJECTFACTORY_H
