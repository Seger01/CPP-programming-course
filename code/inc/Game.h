#ifndef GAME_H
#define GAME_H

#include "Database.h"
#include "Location.h"
#include "String.h"
#include "Vector.h"

class Game {
public:
    Game();
    ~Game();

    void start();
    void end();
    void update();

    void generateDungeon(int amountOfRooms);
    Location* getCurrentLocation();
    void setLocations(Vector<Location*> locations);

    int amountOfLocations();

    void setNewCurrentLocation(int newLocation);

    GameObject* takeObject(String objectName);

    // void look(String item);
    // void search(String item);
    // void go(String direction);
    // void take(String item);
    // void drop(String item);
    // void inspect(String item);
    // void attack(String enemy);
    // void equip(String item);
    // void wait();
    // void consume(String item);
    // void godmode();

    void generateRooms(int amountOfRooms);
    void generateObjectsInRooms(int amountOfRooms);
    void generateEnemies(int amountOfRooms);

    GameObject* getDefaultWeapon();

private:
    int getObjectIndex(String objectName, Vector<Vector<String>> objectInfo);

    Vector<Vector<String>> getObjectInfo();
    Vector<Vector<String>> getRoomInfo();
    Vector<Vector<String>> getEnemiesInfo();
    // Vector<String> getRandomRoom(Vector<Vector<String>>& roomInfo);

    GameObject* getObject(Vector<Vector<String>> objectInfo, int objectnr);

    int getRandomNumber(int min, int max);

private:
    Database db;

    int currentLocation;
    Vector<Location*> locations;
};

#endif // GAME_H
