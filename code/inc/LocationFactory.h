#ifndef LOCATIONFACTORY_H
#define LOCATIONFACTORY_H

#include "Location.h"

class LocationFactory {
public:
    LocationFactory();
    Location* createLocation(const char* name, const char* description);
};

#endif // LOCATIONFACTORY_H
