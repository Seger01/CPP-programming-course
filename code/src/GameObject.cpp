#include "GameObject.h"
#include <cstring>

GameObject::GameObject(String name, String description) : name(name), description(description) {}

void GameObject::setData(String name, String description, int min, int max, int protection) {
    this->name = name;
    this->description = description;

    this->min = min;
    this->max = max;
    this->protection = protection;
}

void GameObject::printName() const { std::cout << "Name: " << name << std::endl; }

void GameObject::printDescription() const { std::cout << "Description: " << description << std::endl; }

GameObject* GameObject::create() { return new GameObject("", ""); }
