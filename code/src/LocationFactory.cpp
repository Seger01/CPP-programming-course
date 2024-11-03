#include "LocationFactory.h"

LocationFactory::LocationFactory() {}

Location* LocationFactory::createLocation(String name, String description) {
    return new Location(0, name, description);
}
