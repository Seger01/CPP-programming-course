#include "Location.h"

#include <cstring>

#include "GameObject.h"

Location::Location(int id, String name, String description) {
    this->name = name;
    this->description = description;

    this->ID = id;

    for (int i = 0; i < 4; i++)
        this->exits.push_back(-1);
}

Location::~Location() {
    for (int i = 0; i < hiddenObjects.size(); ++i) {
    }
}

void Location::addExit(int locationID, int direction) { exits[direction] = locationID; }

void Location::removeExit(int direction) { exits[direction] = -1; }

void Location::addHiddenObject(GameObject* object) { hiddenObjects.push_back(object); }

void Location::addVisibleObject(GameObject* object) {
    visibleObjects.push_back(object);

    for (int i = 0; i < visibleObjects.size(); ++i) {
        std::cout << visibleObjects[i]->getName() << std::endl;
    }
}

void Location::removeHiddenObject(GameObject* object) {
    for (int i = 0; i < hiddenObjects.size(); ++i) {
        if (hiddenObjects[i] == object) {
            hiddenObjects.erase(i);
            return;
        }
    }
}

void Location::removeVisibleObject(GameObject* object) {
    for (int i = 0; i < visibleObjects.size(); ++i) {
        if (visibleObjects[i] == object) {
            visibleObjects.erase(i);
            return;
        }
    }
}

Vector<GameObject*>& Location::getVisibleObjects() { return visibleObjects; }

Vector<GameObject*>& Location::getHiddenObjects() { return hiddenObjects; }

Vector<Enemy*>& Location::getEnemies() { return enemies; }

Vector<int> Location::getExits() { return exits; }

void Location::addEnemy(Enemy* enemy) { enemies.push_back(enemy); }

void Location::removeEnemy(Enemy* enemy) {
    for (int i = 0; i < enemies.size(); ++i) {
        if (enemies[i] == enemy) {
            enemies.erase(i);
            return;
        }
    }
}

String Location::getName() const { return name; }

String Location::getDescription() const { return description; }
