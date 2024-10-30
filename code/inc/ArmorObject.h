#ifndef ARMOROBJECT_H
#define ARMOROBJECT_H

#include "GameObject.h"

class ArmorObject : public GameObject {
public:
    ArmorObject(const char* name, const char* description, int defense);

    static GameObject* create();

private:
    static const bool registered;
    int defense;
};

#endif // ARMOROBJECT_H
