#include "GameObjectFactory.h"

GameObject* GameObjectFactory::createProduct(const char* id) const {
    for (int i = 0; i < m_registeredCount; ++i) {
        if (std::strcmp(m_ids[i], id) == 0) {
            return m_creators[i]();
        }
    }
    return nullptr;
}

GameObject* GameObjectFactory::createProduct(const char* id, const char* name, const char* description, int min,
                                             int max, int protection) const {
    GameObject* product = createProduct(id);
    if (product) {
        product->setData(name, description, min, max, protection);
    }
    return product;
}

bool GameObjectFactory::registerProduct(const char* id, CreatorFunc creator) {
    if (m_registeredCount >= MAX_PRODUCTS)
        return false; // Array full

    m_ids[m_registeredCount] = id;
    m_creators[m_registeredCount] = creator;
    ++m_registeredCount;
    return true;
}

GameObjectFactory& GameObjectFactory::instance() {
    static GameObjectFactory factoryInstance;
    return factoryInstance;
}
