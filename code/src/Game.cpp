#include "Game.h"

#include <cstddef>
#include <cstring>
#include <random>

#include "ArmorObject.h"
#include "Directions.h"
#include "Enemy.h"
#include "EnemyFactory.h"
#include "GameObjectFactory.h"
#include "LocationParser.h"
#include "Random.h"

Game::Game() : db("kerkersendraken.db"), currentLocation(0) {}

Game::~Game() { end(); }

void Game::start() {
    if (!db.open()) {
        std::cerr << "Error opening database." << std::endl;
        return;
    }
}

void Game::end() { db.close(); }

void Game::update() {
    // Placeholder for game update logic
}

Location* Game::getCurrentLocation() {
    // Placeholder for getting the current location
    return locations[currentLocation];
}

void Game::setLocations(Vector<Location*> locations) {
    this->locations = locations;
    Vector<Vector<String>> objectInfo = getObjectInfo();
    Vector<Vector<String>> enemyInfo = getEnemiesInfo();

    for (int i = 0; i < locations.size(); i++) {
        for (int j = 0; j < locations[i]->getVisibleObjects().size(); j++) {
            int objectnr = getObjectIndex(locations[i]->getVisibleObjects()[j]->getName(), objectInfo);

            GameObject* object = getObject(objectInfo, objectnr);

            delete locations[i]->getVisibleObjects()[j];
            locations[i]->getVisibleObjects()[j] = object;
        }

        for (int j = 0; j < locations[i]->getHiddenObjects().size(); j++) {
            int objectnr = getObjectIndex(locations[i]->getHiddenObjects()[j]->getName(), objectInfo);

            GameObject* object = getObject(objectInfo, objectnr);

            delete locations[i]->getHiddenObjects()[j];
            locations[i]->getHiddenObjects()[j] = object;
        }

        for (int j = 0; j < locations[i]->getEnemies().size(); j++) {
            int objectnr = getEnemyIndex(locations[i]->getEnemies()[j]->getName(), enemyInfo);

            Enemy* object = getEnemy(objectInfo, enemyInfo, objectnr);

            delete locations[i]->getEnemies()[j];
            locations[i]->getEnemies()[j] = object;
        }
    }
}

int Game::amountOfLocations() { return locations.size(); }

int Game::getRandomNumber(int min, int max) { return Random::getInstance().generateIntInRange(min, max); }

void Game::setNewCurrentLocation(int newLocation) {
    for (int i = 0; i < locations.size(); i++) {
        if (locations[i]->getID() == newLocation) {
            currentLocation = i;
            return;
        }
    }

    currentLocation = newLocation;
}

GameObject* Game::takeObject(String objectName) {
    Vector<GameObject*>& objects = locations[currentLocation]->getVisibleObjects();

    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->getName() == objectName) {
            GameObject* object = objects[i];
            objects.erase(i);
            return object;
        }
    }

    std::cout << "no object matches the name: " << objectName << std::endl;
    // if nothing found return nullptr
    return nullptr;
}

GameObject* Game::getDefaultWeapon() {
    Vector<Vector<String>> objectInfo = getObjectInfo();

    int dolkIndex = -1;
    for (int i = 0; i < objectInfo.size(); i++) {
        if (objectInfo[i][0] == "dolk") {
            dolkIndex = i;
            break;
        }
    }

    String objectName = objectInfo[dolkIndex][0];
    String objectDescription = objectInfo[dolkIndex][1];

    int objectMin = (objectInfo[dolkIndex][3].empty() || objectInfo[dolkIndex][3] == "NULL")
                        ? 0
                        : std::stoi(objectInfo[dolkIndex][3].c_str());

    int objectMax = (objectInfo[dolkIndex][4].empty() || objectInfo[dolkIndex][4] == "NULL")
                        ? 0
                        : std::stoi(objectInfo[dolkIndex][4].c_str());

    int objectProtection = (objectInfo[dolkIndex][5].empty() || objectInfo[dolkIndex][5] == "NULL")
                               ? 0
                               : std::stoi(objectInfo[dolkIndex][5].c_str());

    GameObject* object = GameObjectFactory::instance().createObject(objectInfo[dolkIndex][2], objectName);

    object->setData(object->getName(), objectDescription, objectMin, objectMax, objectProtection);
    return object;
}

void Game::addScoreToDB(String playerName, int score) {
    // Prepare the SQL insert statement with direct values
    std::string insertSQL = "INSERT INTO Leaderboard (naam, goudstukken) VALUES ('" + std::string(playerName.c_str()) +
                            "', " + std::to_string(score) + ");";

    // Use your db object to execute the insert statement
    if (!db.execute(insertSQL.c_str())) {
        std::cout << "Error inserting into leaderboard." << std::endl;
    } else {
    }
}
Vector<Vector<String>> Game::getLeaderboardEntries() {
    Vector<Vector<String>> leaderboardEntries;

    // Query the leaderboard table
    const char* selectSQL = "SELECT * FROM Leaderboard ORDER BY goudstukken DESC LIMIT 10;";
    if (db.executeQuery(selectSQL, leaderboardEntries) == false) {
        std::cout << "Error querying leaderboard." << std::endl;
    }

    return leaderboardEntries;
}

void Game::generateDungeon(int amountOfRooms) {
    generateRooms(amountOfRooms);
    generateObjectsInRooms(amountOfRooms);
    generateEnemies(amountOfRooms);
}

void Game::generateRooms(int amountOfRooms) {
    Vector<Vector<String>> roomInfo = getRoomInfo();

    if (roomInfo.size() < amountOfRooms) {
        std::cerr << "Not enough rooms in the database." << std::endl;
        exit(1);
        return;
    }

    for (int i = 0; i < amountOfRooms; i++) {
        int roomnr = getRandomNumber(0, roomInfo.size() - 2);
        Vector<String> room = roomInfo[roomnr];
        roomInfo.erase(roomnr);

        locations.push_back(new Location(i, room[0], room[1]));
    }

    // Create a spanning tree for guaranteed connectivity
    for (int i = 1; i < amountOfRooms; ++i) {
        int direction = getRandomNumber(0, 3);   // Random direction for the exit (0: North, 1: West, 2: South, 3:
                                                 // East)
        locations[i]->addExit(i - 1, direction); // Connect current location to previous one
        // Add the opposite exit
        locations[i - 1]->addExit(i, (direction + 2) % 4); // The opposite direction
    }

    // Now add random exits to increase connectivity while maintaining reachability
    for (int i = 0; i < amountOfRooms; ++i) {
        for (int direction = 0; direction < 4; ++direction) { // 0: North, 1: West, 2: South, 3: East
            // Randomly decide whether to create an additional exit
            if (getRandomNumber(0, 2) % 2 == 0) {                           // 50% chance to link to another location
                int linkedLocation = getRandomNumber(0, amountOfRooms - 1); // Pick a random location to link
                // Ensure we are not linking the exit to itself
                if (linkedLocation != i) {
                    locations[i]->addExit(linkedLocation, direction);
                }
            } else {
                // No exit in this direction; you may want to set it to a sentinel value like -1 to indicate no exit
                locations[i]->removeExit(direction);
            }
        }
    }
}

Enemy* Game::getEnemy(Vector<Vector<String>> objectInfo, Vector<Vector<String>> enemiesInfo, int objectnr) {

    int enemyType = objectnr;

    String enemyName = (enemiesInfo[enemyType][0].empty() || enemiesInfo[enemyType][0] == "NULL")
                           ? String("")
                           : enemiesInfo[enemyType][0];

    String enemyDiscription = (enemiesInfo[enemyType][1].empty() || enemiesInfo[enemyType][1] == "NULL")
                                  ? String("")
                                  : enemiesInfo[enemyType][1];

    int health = (enemiesInfo[enemyType][4].empty() || enemiesInfo[enemyType][4] == "NULL")
                     ? 0
                     : std::stoi(enemiesInfo[enemyType][4].c_str());

    int hitChangePercent = (enemiesInfo[enemyType][5].empty() || enemiesInfo[enemyType][5] == "NULL")
                               ? 0
                               : std::stoi(enemiesInfo[enemyType][5].c_str());

    int minDamage = (enemiesInfo[enemyType][6].empty() || enemiesInfo[enemyType][6] == "NULL")
                        ? 0
                        : std::stoi(enemiesInfo[enemyType][6].c_str());

    int maxDamage = (enemiesInfo[enemyType][7].empty() || enemiesInfo[enemyType][7] == "NULL")
                        ? 0
                        : std::stoi(enemiesInfo[enemyType][7].c_str());

    Enemy* enemy = nullptr;

    enemy = EnemyFactory::instance().createEnemy(enemyName);
    enemy->setData(enemy->getName(), enemyDiscription, health, hitChangePercent, minDamage, maxDamage);

    int minEnemyObjects = enemiesInfo[enemyType][2].empty() ? 0 : std::stoi(enemiesInfo[enemyType][2].c_str());
    int maxEnemyObjects = enemiesInfo[enemyType][3].empty() ? 0 : std::stoi(enemiesInfo[enemyType][3].c_str());

    // generate a random amount of objects for the enemy
    int amountOfObjects = getRandomNumber(minEnemyObjects, maxEnemyObjects);
    for (int i = 0; i < amountOfObjects; i++) {
        int objectnr = getRandomNumber(0, objectInfo.size() - 1);

        GameObject* object = getObject(objectInfo, objectnr);

        enemy->addObject(object);
    }

    return enemy;
}

GameObject* Game::getObject(Vector<Vector<String>> objectInfo, int objectnr) {

    String objectName = objectInfo[objectnr][0];
    String objectDescription = objectInfo[objectnr][1];

    int objectMin = (objectInfo[objectnr][3].empty() || objectInfo[objectnr][3] == "NULL")
                        ? 0
                        : std::stoi(objectInfo[objectnr][3].c_str());

    int objectMax = (objectInfo[objectnr][4].empty() || objectInfo[objectnr][4] == "NULL")
                        ? 0
                        : std::stoi(objectInfo[objectnr][4].c_str());

    int objectProtection = (objectInfo[objectnr][5].empty() || objectInfo[objectnr][5] == "NULL")
                               ? 0
                               : std::stoi(objectInfo[objectnr][5].c_str());

    GameObject* object = GameObjectFactory::instance().createObject(objectInfo[objectnr][2], objectName);

    object->setData(object->getName(), objectDescription, objectMin, objectMax, objectProtection);

    return object;
}

void Game::generateObjectsInRooms(int amountOfRooms) {
    Vector<Vector<String>> objectInfo = getObjectInfo();

    for (int i = 0; i < amountOfRooms; i++) {
        int amountOfVisibleObjects = getRandomNumber(0, 3);
        int amountOfHiddenObjects = getRandomNumber(0, 2);

        for (int j = 0; j < amountOfVisibleObjects; j++) {
            int objectnr = getRandomNumber(0, objectInfo.size() - 1);

            GameObject* object = getObject(objectInfo, objectnr);

            locations[i]->addVisibleObject(object);
        }

        for (int j = 0; j < amountOfHiddenObjects; j++) {
            int objectnr = getRandomNumber(0, objectInfo.size() - 1);

            GameObject* object = getObject(objectInfo, objectnr);

            locations[i]->addHiddenObject(object);
        }
    }
}

void Game::generateEnemies(int amountOfRooms) {
    Vector<Vector<String>> objectInfo = getObjectInfo();

    int amountOfEnemies = std::ceil(amountOfRooms / 3);
    Vector<Vector<String>> enemiesInfo = getEnemiesInfo();

    for (int i = 0; i < amountOfEnemies; i++) {
        int locationnr = getRandomNumber(0, amountOfRooms - 1);
        int enemyType = getRandomNumber(0, enemiesInfo.size() - 1);

        Enemy* enemy = getEnemy(objectInfo, enemiesInfo, enemyType);

        locations[locationnr]->addEnemy(enemy);
    }
}

int Game::getObjectIndex(String objectName, Vector<Vector<String>> objectInfo) {
    for (int i = 0; i < objectInfo.size(); i++) {
        if (objectInfo[i][0] == objectName) {
            return i;
        }
    }

    return -1;
}

int Game::getEnemyIndex(String objectName, Vector<Vector<String>> enemyInfo) {
    for (int i = 0; i < enemyInfo.size(); i++) {
        if (enemyInfo[i][0] == objectName) {
            return i;
        }
    }

    return -1;
}

Vector<Vector<String>> Game::getEnemiesInfo() {
    Vector<Vector<String>> enemiesInfo;

    // Query the table
    const char* selectSQL = "SELECT * FROM Vijanden;";
    if (db.executeQuery(selectSQL, enemiesInfo) == false) {
        std::cout << "Error querying table." << std::endl;
    }

    return enemiesInfo;
}

Vector<Vector<String>> Game::getRoomInfo() {
    Vector<Vector<String>> roomInfo;

    // Query the table
    const char* selectSQL = "SELECT * FROM Locaties;";
    if (db.executeQuery(selectSQL, roomInfo) == false) {
        std::cout << "Error querying table." << std::endl;
    }

    return roomInfo;
}

Vector<Vector<String>> Game::getObjectInfo() {
    Vector<Vector<String>> roomInfo;

    // Query the table
    const char* selectSQL = "SELECT * FROM Objecten;";
    if (db.executeQuery(selectSQL, roomInfo) == false) {
        std::cout << "Error querying table." << std::endl;
    }

    return roomInfo;
}
