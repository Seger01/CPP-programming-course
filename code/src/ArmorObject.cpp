#include "ArmorObject.h"

#include "GameObject.h"
#include "GameObjectFactory.h"

const bool ArmorObject::registered = GameObjectFactory::instance().registerObject("wapenrusting", ArmorObject::create);

ArmorObject::ArmorObject() : GameObject() {}

ArmorObject::ArmorObject(String name, String description, int min, int max, int defense)
    : GameObject(name, description, min, max, defense) {}

GameObject* ArmorObject::create() { return new ArmorObject(); }
