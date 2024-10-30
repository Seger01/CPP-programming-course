#include "GameObject.h"
#include <cstring>

GameObject::GameObject(const char* name, const char* description) {
    strncpy(this->name, name, sizeof(this->name));
    strncpy(this->description, description, sizeof(this->description));
}
