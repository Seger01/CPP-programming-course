#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "GameObject.h"

class GameObjectFactory {
public:
    GameObjectFactory();
    GameObject* createGameObject(const char* name, const char* description);
};

#endif // GAMEOBJECTFACTORY_H
