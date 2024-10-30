#ifndef LOCATION_H
#define LOCATION_H

#include <vector>

class GameObject;
class Enemy;

class Location {
public:
    Location(const char* name, const char* description);

private:
    char name[50];
    char description[200];

    std::vector<GameObject*> gameObjects;
    std::vector<Enemy*> enemies;
};

#endif // LOCATION_H
