#include "GameObjectFactory.h"

GameObject* GameObjectFactory::createObject(String id) const {
    for (int i = 0; i < m_creators.size(); ++i) {
        if (m_ids[i] == id) {
            return m_creators[i]();
        }
    }
    return nullptr;
}

bool GameObjectFactory::registerObject(String id, CreatorFunc creator) {
    m_ids.push_back(id);
    m_creators.push_back(creator);
    return true;
}

GameObjectFactory& GameObjectFactory::instance() {
    static GameObjectFactory factoryInstance;
    return factoryInstance;
}
