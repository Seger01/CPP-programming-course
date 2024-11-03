#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Enemy.h"

class EnemyFactory {
public:
    EnemyFactory();
    Enemy* createEnemy(String name);

    static EnemyFactory& instance();

private:
    int objectNameSeen(String objectName);
    void increaseObjectNameSeen(String objectName);

private:
    Vector<String> objectNames;
    Vector<int> objectNameAmounts;
};

#endif // ENEMYFACTORY_H
