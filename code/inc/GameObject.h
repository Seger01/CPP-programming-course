#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
public:
    GameObject(const char* name, const char* description);

protected:
    char name[50];
    char description[200];
};

#endif // GAMEOBJECT_H
