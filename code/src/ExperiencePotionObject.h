#include "ExperiencePotionObject.h"

ExperiencePotionObject::ExperiencePotionObject(const char* name, const char* description, int experienceAmount)
    : ConsumableObject(name, description), experienceAmount(experienceAmount) {}
