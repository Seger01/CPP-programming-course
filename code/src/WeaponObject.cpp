#include "WeaponObject.h"

#include "GameObject.h"
#include "GameObjectFactory.h"

const bool WeaponObject::registered = GameObjectFactory::instance().registerObject("wapen", WeaponObject::create);

WeaponObject::WeaponObject() : GameObject("", "") {}

WeaponObject::WeaponObject(String name, String description, int min, int max, int defense)
    : GameObject(name, description, min, max, defense) {}

GameObject* WeaponObject::create() { return new WeaponObject(); }
