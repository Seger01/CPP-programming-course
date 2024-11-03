#include "HealthPotionObject.h"

#include "ConsumableObject.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

const bool HealthPotionObject::registered =
    GameObjectFactory::instance().registerObject("levenselixer", HealthPotionObject::create);

HealthPotionObject::HealthPotionObject() : ConsumableObject() {}

HealthPotionObject::HealthPotionObject(String name, String description, int min, int max, int value)
    : ConsumableObject(name, description, min, max, value) {}

GameObject* HealthPotionObject::create() { return new HealthPotionObject(); }
