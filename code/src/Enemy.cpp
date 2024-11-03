#include "Enemy.h"
#include <cstring>

Enemy::Enemy(String name, String description, int health, int hitChancePercent, int minDamage, int maxDamage)
    : name(name), description(description), health(health), hitChancePercent(hitChancePercent), minDamage(minDamage),
      maxDamage(maxDamage) {}

String Enemy::getName() const { return name; }

String Enemy::getDescription() const { return description; }

int Enemy::getHealth() const { return health; }

void Enemy::setHealth(int health) { this->health = health; }

int Enemy::getHitChancePercent() const { return hitChancePercent; }

int Enemy::getMinDamage() const { return minDamage; }

int Enemy::getMaxDamage() const { return maxDamage; }

void Enemy::setName(String name) { this->name = name; }

void Enemy::setData(String name, String description, int health, int hitChancePercent, int minDamage, int maxDamage) {
    this->name = name;
    this->description = description;
    this->health = health;
    this->hitChancePercent = hitChancePercent;
    this->minDamage = minDamage;
    this->maxDamage = maxDamage;
}

Vector<GameObject*>& Enemy::getInventory() { return inventory; }

void Enemy::addObject(GameObject* gameObject) { inventory.push_back(gameObject); }

void Enemy::removeObject(GameObject* gameObject) {
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i] == gameObject) {
            inventory.erase(i);
            return;
        }
    }
}
