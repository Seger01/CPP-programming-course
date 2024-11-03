#ifndef LOCATION_H
#define LOCATION_H

#include "String.h"
#include "Vector.h"

class GameObject;
class Enemy;

class Location {
public:
    Location(int ID, String name, String description);
    ~Location();

    void revealObjects();

    void addExit(int locationID, int direction);
    void removeExit(int direction);

    void addHiddenObject(GameObject* object);
    void addVisibleObject(GameObject* object);

    void removeHiddenObject(GameObject* object);
    void removeVisibleObject(GameObject* object);

    Vector<GameObject*>& getVisibleObjects();
    Vector<GameObject*>& getHiddenObjects();
    Vector<Enemy*>& getEnemies();

    Vector<int> getExits();

    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enemy);

    String getName() const;
    String getDescription() const;

    int getID() const;

private:
    String name;
    String description;

    Vector<GameObject*> hiddenObjects;
    Vector<GameObject*> visibleObjects;

    Vector<Enemy*> enemies;

    int ID;

    Vector<int> exits;
};

#endif // LOCATION_H
