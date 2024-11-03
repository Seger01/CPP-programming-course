#ifndef GOLDPIECESOBJECT_H
#define GOLDPIECESOBJECT_H

#include "GameObject.h"

class GoldPiecesObject : public GameObject {
public:
    GoldPiecesObject();
    GoldPiecesObject(String name, String description, int min, int max, int defense);

    String getType() const override { return type; }

    static GameObject* create();

private:
    String type = "goudstukken";

    static const bool registered;
};

#endif // GOLDPIECESOBJECT_H
