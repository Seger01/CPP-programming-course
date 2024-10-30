#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Enemy.h"

class EnemyFactory {
public:
    EnemyFactory();
    Enemy* createEnemy(const char* name, const char* description, int health, int damage, int experience);
};

#endif // ENEMYFACTORY_H
