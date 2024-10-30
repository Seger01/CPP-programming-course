#include "LocationFactory.h"

LocationFactory::LocationFactory() {}

Location* LocationFactory::createLocation(const char* name, const char* description) {
    return new Location(name, description);
}
