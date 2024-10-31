#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "String.h"
#include <iostream>

class GameObject {
public:
    GameObject(String name, String description);

    virtual void printName() const;
    virtual void printDescription() const;

    static GameObject* create();

    virtual void setData(String name, String description, int min = 0, int max = 0, int protection = 0);

protected:
    String name;
    String description;

    int min;
    int max;
    int protection;
};

#endif // GAMEOBJECT_H
