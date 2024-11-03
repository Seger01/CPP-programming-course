#include "GameObjectFactory.h"

int GameObjectFactory::objectNameSeen(String objectName) {
    for (int i = 0; i < objectNames.size(); i++) {
        if (objectNames[i] == objectName) {
            return objectNameAmounts[i];
        }
    }
    return 0;
}

void GameObjectFactory::increaseObjectNameSeen(String objectName) {
    for (int i = 0; i < objectNames.size(); i++) {
        if (objectNames[i] == objectName) {
            objectNameAmounts[i] = objectNameAmounts[i] + 1;
            return;
        }
    }
    objectNames.push_back(objectName);
    objectNameAmounts.push_back(1);
}

GameObject* GameObjectFactory::createObject(String id, String objectName) {
    for (int i = 0; i < m_creators.size(); ++i) {
        if (m_ids[i] == id) {
            GameObject* object = m_creators[i]();

            if (this->objectNameSeen(objectName) != 0) {
                String newObjectName = objectName;
                newObjectName.append(std::to_string(this->objectNameSeen(objectName)).c_str());
                object->setName(newObjectName);
            } else {
                object->setName(objectName);
            }

            this->increaseObjectNameSeen(objectName);

            return object;
        }
    }
    std::cout << "No object with ID " << id << " found." << std::endl;
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
