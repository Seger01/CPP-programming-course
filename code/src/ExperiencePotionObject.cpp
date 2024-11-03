#include "ExperiencePotionObject.h"
#include "ConsumableObject.h"

#include "GameObject.h"
#include "GameObjectFactory.h"

const bool ExperiencePotionObject::registered =
    GameObjectFactory::instance().registerObject("ervaringsdrank", ExperiencePotionObject::create);

ExperiencePotionObject::ExperiencePotionObject() : ConsumableObject() {}

ExperiencePotionObject::ExperiencePotionObject(String name, String description, int min, int max, int value)
    : ConsumableObject(name, description, min, max, value) {}

GameObject* ExperiencePotionObject::create() { return new ExperiencePotionObject(); }
