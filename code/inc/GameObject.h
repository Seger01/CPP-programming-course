#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>

class GameObject {
public:
    GameObject(const char* name, const char* description);

    virtual void printName() const;
    virtual void printDescription() const;

    static GameObject* create();

    virtual void setData(const char* name, const char* description, int min = 0, int max = 0, int protection = 0);

protected:
    char name[50];
    char description[200];

    int min;
    int max;
    int protection;
};

#endif // GAMEOBJECT_H
