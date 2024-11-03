#include "ConsumableObject.h"

ConsumableObject::ConsumableObject() : GameObject() {}

ConsumableObject::ConsumableObject(String name, String description, int min, int max, int value)
    : GameObject(name, description, min, max, value) {}
