#include "ArmorObject.h"

ArmorObject::ArmorObject(const char* name, const char* description, int defense)
    : GameObject(name, description), defense(defense) {}
