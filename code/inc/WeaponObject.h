#ifndef WEAPONOBJECT_H
#define WEAPONOBJECT_H

#include "GameObject.h"

class WeaponObject : public GameObject {
public:
    WeaponObject();
    WeaponObject(String name, String description, int min, int max, int defense);

    static GameObject* create();

private:
    static const bool registered;
};

#endif // WEAPONOBJECT_H
