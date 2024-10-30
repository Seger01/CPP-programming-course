#ifndef EXPERIENCEPOTIONOBJECT_H
#define EXPERIENCEPOTIONOBJECT_H

#include "ConsumableObject.h"

class ExperiencePotionObject : public ConsumableObject {
public:
    ExperiencePotionObject(const char* name, const char* description, int experienceAmount);

private:
    int experienceAmount;
};

#endif // EXPERIENCEPOTIONOBJECT_H
