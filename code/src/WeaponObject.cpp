#include "WeaponObject.h"

WeaponObject::WeaponObject(const char* name, const char* description, int minDamage, int maxDamage)
    : GameObject(name, description), minDamage(minDamage), maxDamage(maxDamage) {}
