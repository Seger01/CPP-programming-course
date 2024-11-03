#ifndef LOCATIONFACTORY_H
#define LOCATIONFACTORY_H

#include "Location.h"
#include "String.h"

class LocationFactory {
public:
    LocationFactory();
    Location* createLocation(String name, String description);
};

#endif // LOCATIONFACTORY_H
