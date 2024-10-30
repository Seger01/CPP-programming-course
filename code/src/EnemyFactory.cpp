#include "EnemyFactory.h"

EnemyFactory::EnemyFactory() {}

Enemy* EnemyFactory::createEnemy(const char* name, const char* description, int health, int damage, int experience) {
    return new Enemy(name, description, health, damage, experience);
}
