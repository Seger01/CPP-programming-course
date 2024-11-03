#ifndef ARMOROBJECT_H
#define ARMOROBJECT_H

#include "GameObject.h"

class ArmorObject : public GameObject {
public:
    ArmorObject();
    ArmorObject(String name, String description, int min, int max, int defense);

    static GameObject* create();

    String getType() const override { return type; }

private:
    String type = "wapenrusting";
    static const bool registered;
};

#endif // ARMOROBJECT_H
