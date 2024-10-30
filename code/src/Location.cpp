#include "Location.h"
#include <cstring>

Location::Location(const char* name, const char* description) {
    strncpy(this->name, name, sizeof(this->name));
    strncpy(this->description, description, sizeof(this->description));
}
