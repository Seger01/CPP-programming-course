#ifndef HEALTHPOTIONOBJECT_H
#define HEALTHPOTIONOBJECT_H

#include "ConsumableObject.h"

class HealthPotionObject : public ConsumableObject {
public:
    HealthPotionObject(const char* name, const char* description, int healAmount);

private:
    int healAmount;
};

#endif // HEALTHPOTIONOBJECT_H
