#include "GameObject.h"
#include <cstring>

GameObject::GameObject(const char* name, const char* description) {
    strncpy(this->name, name, sizeof(this->name));
    strncpy(this->description, description, sizeof(this->description));
}

void GameObject::setData(const char* name, const char* description, int min, int max, int protection) {
    strncpy(this->name, name, sizeof(this->name));
    strncpy(this->description, description, sizeof(this->description));
    this->min = min;
    this->max = max;
    this->protection = protection;
}

void GameObject::printName() const { std::cout << "Name: " << name << std::endl; }

void GameObject::printDescription() const { std::cout << "Description: " << description << std::endl; }

GameObject* GameObject::create() { return new GameObject("", ""); }
