#ifndef TELEPORTATIONPOTIONOBJECT_H
#define TELEPORTATIONPOTIONOBJECT_H

#include "ConsumableObject.h"

class TeleportationPotionObject : public ConsumableObject {
public:
    TeleportationPotionObject();
    TeleportationPotionObject(String name, String description, int min, int max, int defense);

    static GameObject* create();

private:
    static const bool registered;
};

#endif // TELEPORTATIONPOTIONOBJECT_H
