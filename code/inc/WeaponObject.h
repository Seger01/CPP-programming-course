#ifndef WEAPONOBJECT_H
#define WEAPONOBJECT_H

#include "GameObject.h"

class WeaponObject : public GameObject {
public:
    WeaponObject(const char* name, const char* description, int minDamage, int maxDamage);

private:
    int minDamage;
    int maxDamage;
};

#endif // WEAPONOBJECT_H
