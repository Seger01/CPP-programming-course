#include "HealthPotionObject.h"

HealthPotionObject::HealthPotionObject(const char* name, const char* description, int healAmount)
    : ConsumableObject(name, description), healAmount(healAmount) {}
