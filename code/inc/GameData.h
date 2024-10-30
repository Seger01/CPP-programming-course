#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Database.h"

class GameData {
public:
    GameData(const char* dbName);

    // Example methods for retrieving data
    bool getEnemies(char results[][50], int& rowCount, int& colCount);
    bool getLocations(char results[][50], int& rowCount, int& colCount);
    bool getItems(char results[][50], int& rowCount, int& colCount);

private:
    Database db;
};

#endif // GAMEDATA_H
