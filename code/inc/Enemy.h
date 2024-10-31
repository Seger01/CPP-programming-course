#ifndef ENEMY_H
#define ENEMY_H

#include "String.h"

class Enemy {
public:
    Enemy(String name, String description, int health, int damage, int experience);

private:
    String name;
    String description;
    int health;
    int damage;
    int experience;
};

#endif // ENEMY_H
