#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "String.h"
#include <iostream>

class GameObject {
public:
    GameObject();
    GameObject(String name, String description);
    GameObject(String name, String description, int min, int max, int value);

    virtual ~GameObject() {}

    String& getName();
    String& getDescription();

    int getMin() const;
    int getMax() const;
    int getValue() const;

    static GameObject* create();

    virtual String getType() const { return type; }

    virtual void setName(String name);
    virtual void setData(String name, String description, int min = 0, int max = 0, int value = 0);

protected:
    String name;
    String description;
    String type = "object";

    int min;
    int max;
    int value;
};

#endif // GAMEOBJECT_H
