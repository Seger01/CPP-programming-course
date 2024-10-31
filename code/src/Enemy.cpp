#include "Enemy.h"
#include <cstring>

Enemy::Enemy(String name, String description, int health, int damage, int experience)
    : health(health), damage(damage), experience(experience) {
    this->name = name;
    this->description = description;
}
