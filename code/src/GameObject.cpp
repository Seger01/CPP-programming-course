#include "GameObject.h"
#include <cstring>

GameObject::GameObject() : name(""), description("") {}

GameObject::GameObject(String name, String description) : name(name), description(description) {}

GameObject::GameObject(String name, String description, int min, int max, int protection)
    : name(name), description(description), min(min), max(max), value(protection) {}

String& GameObject::getName() { return name; }

String& GameObject::getDescription() { return description; }

int GameObject::getMin() const { return min; }

int GameObject::getMax() const { return max; }

int GameObject::getValue() const { return value; }

void GameObject::setData(String name, String description, int min, int max, int protection) {
    this->name = name;
    this->description = description;

    this->min = min;
    this->max = max;
    this->value = protection;
}

GameObject* GameObject::create() { return new GameObject("", ""); }
