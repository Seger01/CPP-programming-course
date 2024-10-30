#ifndef GOLDPIECESOBJECT_H
#define GOLDPIECESOBJECT_H

#include "GameObject.h"

class GoldPiecesObject : public GameObject {
public:
    GoldPiecesObject(const char* name, const char* description, int value);

private:
    int value;
};

#endif // GOLDPIECESOBJECT_H
