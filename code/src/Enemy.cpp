#include "Enemy.h"
#include <cstring>

Enemy::Enemy(const char* name, const char* description, int health, int damage, int experience)
    : health(health), damage(damage), experience(experience) {
    strncpy(this->name, name, sizeof(this->name));
    strncpy(this->description, description, sizeof(this->description));
}
