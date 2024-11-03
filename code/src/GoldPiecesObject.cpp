#include "GoldPiecesObject.h"

#include "GameObject.h"
#include "GameObjectFactory.h"

const bool GoldPiecesObject::registered =
    GameObjectFactory::instance().registerObject("goudstukken", GoldPiecesObject::create);

GoldPiecesObject::GoldPiecesObject() : GameObject() {}

GoldPiecesObject::GoldPiecesObject(String name, String description, int min, int max, int worth)
    : GameObject(name, description, min, max, worth) {}

GameObject* GoldPiecesObject::create() { return new GoldPiecesObject(); }
