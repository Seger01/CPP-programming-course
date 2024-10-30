#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
    Enemy(const char* name, const char* description, int health, int damage, int experience);

private:
    char name[50];
    char description[200];
    int health;
    int damage;
    int experience;
};

#endif // ENEMY_H
