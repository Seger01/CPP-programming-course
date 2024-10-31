#include "ArmorObject.h"

#include "GameObjectFactory.h"

// // Register ProductA in the factory
const bool ArmorObject::registered = GameObjectFactory::instance().registerObject("wapenrusting", ArmorObject::create);

ArmorObject::ArmorObject(const char* name, const char* description, int defense)
    : GameObject(name, description), defense(defense) {}

GameObject* ArmorObject::create() { return new ArmorObject("", "", 0); }
