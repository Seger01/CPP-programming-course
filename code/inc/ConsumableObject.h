#ifndef CONSUMABLEOBJECT_H
#define CONSUMABLEOBJECT_H

#include "GameObject.h"

class ConsumableObject : public GameObject {
public:
    ConsumableObject();
    ConsumableObject(String name, String description, int min, int max, int value);
};

#endif // CONSUMABLEOBJECT_H
