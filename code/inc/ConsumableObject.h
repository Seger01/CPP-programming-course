#ifndef CONSUMABLEOBJECT_H
#define CONSUMABLEOBJECT_H

#include "GameObject.h"

class ConsumableObject : public GameObject {
public:
    ConsumableObject(const char* name, const char* description);
};

#endif // CONSUMABLEOBJECT_H
