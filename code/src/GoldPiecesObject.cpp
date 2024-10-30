#include "GoldPiecesObject.h"

GoldPiecesObject::GoldPiecesObject(const char* name, const char* description, int value)
    : GameObject(name, description), value(value) {}
