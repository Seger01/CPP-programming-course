#include "EnemyFactory.h"

EnemyFactory::EnemyFactory() {}

Enemy* EnemyFactory::createEnemy(String name, String description, int health, int hitChancePercent, int minDamage,
                                 int maxDamage) {
    return new Enemy(name, description, health, hitChancePercent, minDamage, maxDamage);
}
