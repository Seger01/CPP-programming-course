#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "String.h"
#include "Vector.h"

class Enemy {
public:
    Enemy(String name, String description, int health, int hitChancePercent, int minDamage, int maxDamage);

    String getName() const;
    String getDescription() const;
    int getHealth() const;
    void setHealth(int health);
    int getHitChancePercent() const;
    int getMinDamage() const;
    int getMaxDamage() const;

    Vector<GameObject*>& getInventory();
    void addObject(GameObject* gameObject);
    void removeObject(GameObject* gameObject);

private:
    String name;
    String description;
    int health;
    int hitChancePercent;
    int minDamage;
    int maxDamage;

    Vector<GameObject*> inventory;
};

#endif // ENEMY_H
