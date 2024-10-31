#include "Game.h"

#include <cstddef>
#include <cstring>
#include <random>

#include "Directions.h"
#include "GameObjectFactory.h"

Game::Game() : db("kerkersendraken.db") {}

Game::~Game() { end(); }

void Game::start() {
    if (!db.open()) {
        std::cerr << "Error opening database." << std::endl;
        return;
    }
}

void Game::end() {
    db.close();
    std::cout << "Goodbye!" << std::endl;
}

void Game::update() {
    // Placeholder for game update logic
}

int Game::getRandomNumber(int min, int max) {
    // Seed with a real random value, if available
    std::random_device rd; // Will be used to obtain a seed for the random number engine

    // Create a random number engine
    std::default_random_engine engine(rd()); // Mersenne Twister engine

    // Define the distribution for integers (e.g., 1 to 100)
    std::uniform_int_distribution<int> intDist(min, max);

    return intDist(engine);
}

void Game::generateDungeon(int amountOfRooms) {
    // Placeholder for dungeon generation logic

    Vector<Vector<String>> roomInfo = getRoomInfo();

    for (int i = 0; i < amountOfRooms; i++) {
        int roomnr = getRandomNumber(0, roomInfo.size() - 1);
        Vector<String> room = roomInfo[roomnr];
        roomInfo.erase(roomnr);

        locations.push_back(new Location(i, room[0], room[1]));
    }

    // // Create locations with unique IDs
    // for (int i = 0; i < numberOfLocations; ++i) {
    //     String name = "Location " + std::to_string(i + 1); // or use any naming convention
    //     String description = "This is the description for " + name;
    //     locations.push_back(new Location(i, name, description));
    // }
    //
    // Create a spanning tree for guaranteed connectivity
    for (int i = 1; i < amountOfRooms; ++i) {
        int direction = getRandomNumber(0, 3);   // Random direction for the exit (0: North, 1: West, 2: South, 3: East)
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

    Vector<Vector<String>> objectInfo = getObjectInfo();

    for (int i = 0; i < amountOfRooms; i++) {

        int amountOfVisibleObjects = getRandomNumber(0, 3);
        int amountOfHiddenObjects = getRandomNumber(0, 2);

        for (int j = 0; j < amountOfVisibleObjects; j++) {
            int objectnr = getRandomNumber(0, objectInfo.size() - 1);

            GameObject* object = GameObjectFactory::instance().createObject(objectInfo[objectnr][2]);

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

            object->setData(objectName, objectDescription, objectMin, objectMax, objectProtection);

            locations[i]->addVisibleObject(object);
        }

        for (int j = 0; j < amountOfHiddenObjects; j++) {
            // GameObject* object = GameObjectFactory::instance().createProduct("ArmorObject");
            // locations[i]->addHiddenObject(object);
        }
    }
}

Vector<Vector<String>> Game::getRoomInfo() {
    Vector<Vector<String>> roomInfo;

    if (!db.open()) {
        return roomInfo;
    }

    // Query the table
    const char* selectSQL = "SELECT * FROM Locaties;";
    if (db.executeQuery(selectSQL, roomInfo) == false) {
        std::cout << "Error querying table." << std::endl;
    }

    return roomInfo;
}

Vector<Vector<String>> Game::getObjectInfo() {
    Vector<Vector<String>> roomInfo;

    if (!db.open()) {
        return roomInfo;
    }

    // Query the table
    const char* selectSQL = "SELECT * FROM Objecten;";
    if (db.executeQuery(selectSQL, roomInfo) == false) {
        std::cout << "Error querying table." << std::endl;
    }

    return roomInfo;
}
