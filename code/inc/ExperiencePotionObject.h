#ifndef EXPERIENCEPOTIONOBJECT_H
#define EXPERIENCEPOTIONOBJECT_H

#include "ConsumableObject.h"

class ExperiencePotionObject : public ConsumableObject {
public:
    ExperiencePotionObject();
    ExperiencePotionObject(String name, String description, int min, int max, int defense);

    static GameObject* create();

private:
    static const bool registered;
};

#endif // HEALTHPOTIONOBJECT_H
