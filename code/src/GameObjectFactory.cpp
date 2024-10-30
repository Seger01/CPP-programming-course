#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory() {}

GameObject* GameObjectFactory::createGameObject(const char* name, const char* description) {
    return new GameObject(name, description);
}
