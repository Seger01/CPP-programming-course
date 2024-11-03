#include "EnemyFactory.h"

EnemyFactory::EnemyFactory() {}

Enemy* EnemyFactory::createEnemy(String name) {
    Enemy* enemy = new Enemy(name, 0, 0, 0, 0, 0);

    std::cout << "Creating enemy: " << name << std::endl;
    std::cout << "Amount of times seen: " << this->objectNameSeen(name) << std::endl;

    if (this->objectNameSeen(name) != 0) {
        String newObjectName = name;
        newObjectName.append(std::to_string(this->objectNameSeen(name)).c_str());
        std::cout << newObjectName << std::endl;
        enemy->setName(newObjectName);
    } else {
        enemy->setName(name);
    }

    this->increaseObjectNameSeen(name);

    return enemy;
}

EnemyFactory& EnemyFactory::instance() {
    static EnemyFactory factoryInstance;
    return factoryInstance;
}

int EnemyFactory::objectNameSeen(String objectName) {
    for (int i = 0; i < objectNames.size(); i++) {
        if (objectNames[i] == objectName) {
            return objectNameAmounts[i];
        }
    }
    return 0;
}

void EnemyFactory::increaseObjectNameSeen(String objectName) {
    for (int i = 0; i < objectNames.size(); i++) {
        if (objectNames[i] == objectName) {
            objectNameAmounts[i] = objectNameAmounts[i] + 1;
            return;
        }
    }
    objectNames.push_back(objectName);
    objectNameAmounts.push_back(1);
}
