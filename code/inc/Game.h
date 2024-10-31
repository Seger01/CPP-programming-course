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

private:
    Vector<Vector<String>> getRoomInfo();
    Vector<Vector<String>> getObjectInfo();
    // Vector<String> getRandomRoom(Vector<Vector<String>>& roomInfo);

    int getRandomNumber(int min, int max);

private:
    Database db;

    Vector<Location*> locations;
};

#endif // GAME_H
