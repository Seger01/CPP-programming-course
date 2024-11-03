#include "TeleportationPotionObject.h"

#include "ConsumableObject.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

const bool TeleportationPotionObject::registered =
    GameObjectFactory::instance().registerObject("teleportatiedrank", TeleportationPotionObject::create);

TeleportationPotionObject::TeleportationPotionObject() : ConsumableObject() {}

TeleportationPotionObject::TeleportationPotionObject(String name, String description, int min, int max, int value)
    : ConsumableObject(name, description, min, max, value) {}

GameObject* TeleportationPotionObject::create() { return new TeleportationPotionObject(); }
