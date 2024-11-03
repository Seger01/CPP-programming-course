#ifndef HEALTHPOTIONOBJECT_H
#define HEALTHPOTIONOBJECT_H

#include "ConsumableObject.h"

class HealthPotionObject : public ConsumableObject {
public:
    HealthPotionObject();
    HealthPotionObject(String name, String description, int min, int max, int defense);

    static GameObject* create();

private:
    static const bool registered;
};

#endif // HEALTHPOTIONOBJECT_H
