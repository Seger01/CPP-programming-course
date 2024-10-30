#include "GameData.h"
#include <iostream>

GameData::GameData(const char* dbName) : db(dbName) {
    if (!db.open()) {
        std::cerr << "Failed to open database." << std::endl;
        exit(1);
        // Handle error as needed
    }
}

bool GameData::getEnemies(char results[][50], int& rowCount, int& colCount) {
    // const char* query = "SELECT * FROM enemies;";                      // Adjust table name as necessary
    // return db.executeQuery(query, results, rowCount, colCount, 10, 5); // Adjust max rows and columns as needed
    return true;
}

bool GameData::getLocations(char results[][50], int& rowCount, int& colCount) {
    // const char* query = "SELECT * FROM locations;";                    // Adjust table name as necessary
    // return db.executeQuery(query, results, rowCount, colCount, 10, 5); // Adjust max rows and columns as needed
    return true;
}

bool GameData::getItems(char results[][50], int& rowCount, int& colCount) {
    // const char* query = "SELECT * FROM items;";                        // Adjust table name as necessary
    // return db.executeQuery(query, results, rowCount, colCount, 10, 5); // Adjust max rows and columns as needed
    return true;
}
