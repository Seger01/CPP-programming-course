#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Enemy.h"

class EnemyFactory {
public:
    EnemyFactory();
    Enemy* createEnemy(String name, String description, int health, int hitChancePercent, int minDamage, int maxDamage);
};

#endif // ENEMYFACTORY_H
