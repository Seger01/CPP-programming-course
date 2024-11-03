#include "TUI.h"

#include <iostream>
#include <memory>

#include "ArmorObject.h"
#include "Enemy.h"
#include "ExperiencePotionObject.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "HealthPotionObject.h"
#include "LocationParser.h"
#include "Random.h"
#include "String.h"
#include "TeleportationPotionObject.h"
#include "WeaponObject.h"

TUI::TUI() : log("logfile.txt") { init(); }

TUI::TUI(std::string filename) : xmlFilename(filename), log("logfile.txt") { init(); }

TUI::~TUI() {}

void TUI::init() {

    running = false;

    game = Game();
    game.start();

    player = Player();

    GameObject* object = game.getDefaultWeapon();

    player.addObject(std::unique_ptr<GameObject>(object));
    player.setEquippedWeapon(object->getName());

    if (xmlFilename != "") {
        createGameFromFile();

    } else {
        int amountOfRooms = 10;
        game.generateDungeon(amountOfRooms);
    }
}

void TUI::startup() {
    log << "Give player name: ";

    String playerName = getInput();
    log.addln(std::string(playerName.c_str()));

    player.setName(playerName);
}

void TUI::addScoreToDB() {}

void TUI::displayHighScores() {}

void TUI::endOfGame() {
    log << "Game over." << "\n";

    log << "Final score: " << player.getGold() << "\n";

    game.addScoreToDB(player.getName(), player.getGold());

    Vector<Vector<String>> scores = game.getLeaderboardEntries();

    log << "High scores:" << "\n";
    for (int i = 0; i < scores.size(); i++) {
        log << scores[i][1] << ": " << scores[i][2] << "\n";
    }

    log << "Thanks for playing!" << "\n";
    log << "Play again(y/n): ";

    String input = getInput();
    log.addln(std::string(input.c_str()));

    if (input == "y") {
        restart = true;
        running = false;
    } else {
        restart = false;
        running = false;
    }
}

bool TUI::run() {
    log << "Welcome to Kerkers en Draken! \n";

    startup();

    restart = false;
    running = true;

    while (running) {
        printPrompt();
        handleInput();

        if (player.getHealth() <= 0) {
            endOfGame();
        }
    }

    return restart;
}

void TUI::printPrompt() { log << " > "; }

void TUI::handleInput() {
    String input = getInput();
    log.addln(std::string(input.c_str()));

    String action = input.getFirstWord();

    input.removeFirstWord();
    if (action == "Help") {
        printHelp();
    } else if (action == "Look") {
        look(input);
    } else if (action == "Search") {
        search(input);
    } else if (action == "Go") {
        go(input);
    } else if (action == "Take") {
        take(input);
    } else if (action == "Drop") {
        drop(input);
    } else if (action == "Inspect") {
        inspect(input);
    } else if (action == "Attack") {
        attack(input);
    } else if (action == "Equip") {
        equip(input);
    } else if (action == "Wait") {
        wait();
    } else if (action == "Consume") {
        consume(input);
    } else if (action == "Suicide") {
        suicide();
    } else if (action == "Godmode") {
        godmode();
    } else if (action == "Quit") {
        running = false;
    } else {
        log << "Invalid action." << "\n";
        log << "Type 'Help' for a list of available actions." << "\n";
    }
}

void TUI::suicide() { player.setHealth(0); }

void TUI::look(String item) {
    Location* currentLocation = game.getCurrentLocation();
    if (currentLocation == nullptr) {
        return;
    }
    log << "Location id " << currentLocation->getID() << "\n";
    log << "Location: " << currentLocation->getName() << "\n";
    log << "Description: " << currentLocation->getDescription() << "\n";
    log << "\n";

    log << "Visible objects:" << "\n";
    for (int i = 0; i < currentLocation->getVisibleObjects().size(); i++) {
        log << currentLocation->getVisibleObjects()[i]->getName() << "\n";
    }
    log << "\n";

    log << "Exits:" << "\n";
    for (int i = 0; i < currentLocation->getExits().size(); i++) {
        if (currentLocation->getExits()[i] != -1) {
            switch (i) {
            case 0:
                log << "North" << "\n";
                break;
            case 1:
                log << "East" << "\n";
                break;
            case 2:
                log << "South" << "\n";
                break;
            case 3:
                log << "West" << "\n";
                break;
            }
            log << "Location ID: " << currentLocation->getExits()[i] << "\n";
        }
    }
    log << "\n";

    log << "Enemies:" << "\n";
    for (int i = 0; i < currentLocation->getEnemies().size(); i++) {
        if (currentLocation->getEnemies()[i]->getHealth() == 0) {
            log << "Defeated ";
        }
        log << currentLocation->getEnemies()[i]->getName() << "\n";
    }
    log << "\n";

    log << "Hidden objects:" << "\n";
    for (int i = 0; i < currentLocation->getHiddenObjects().size(); i++) {
        log << currentLocation->getHiddenObjects()[i]->getName() << "\n";
    }
    log << "\n";
}

void TUI::search(String item) {
    log << "Searched" << item << "\n";

    while (game.getCurrentLocation()->getHiddenObjects().size() > 0) {
        GameObject* object = game.getCurrentLocation()->getHiddenObjects()[0];
        game.getCurrentLocation()->addVisibleObject(object);
        game.getCurrentLocation()->removeHiddenObject(object);
    }

    runEnemyTurns();

    return;
}

void TUI::go(String direction) {
    bool directionFound = false;
    int newLocation = -1;

    if (direction == "North") {
        if (game.getCurrentLocation()->getExits()[0] != -1) {
            newLocation = (game.getCurrentLocation()->getExits()[0]);
            directionFound = true;
        }
    } else if (direction == "East") {
        if (game.getCurrentLocation()->getExits()[1] != -1) {
            newLocation = (game.getCurrentLocation()->getExits()[1]);
            directionFound = true;
        }
    } else if (direction == "South") {
        if (game.getCurrentLocation()->getExits()[2] != -1) {
            newLocation = (game.getCurrentLocation()->getExits()[2]);
            directionFound = true;
        }
    } else if (direction == "West") {
        if (game.getCurrentLocation()->getExits()[3] != -1) {
            newLocation = (game.getCurrentLocation()->getExits()[3]);
            directionFound = true;
        }
    } else {
        log << "Invalid direction." << "\n";
    }

    if (directionFound) {
        runEnemyTurns();

        game.setNewCurrentLocation(newLocation);
        log << "Moved to new location." << "\n";
    }
}

void TUI::take(String item) {
    log << "Taking " << item << "\n";

    std::unique_ptr<GameObject> gameObject(game.takeObject(item));

    if (gameObject != nullptr) {
        log << "Adding " << gameObject->getName() << " to inventory." << "\n";
        player.addObject(std::move(gameObject));
    }
}

void TUI::drop(String item) {
    for (auto& object : player.getInventory()) {
        if (object->getName() == item) {
            GameObject* objectPtr = object.release();
            player.removeObject(object);
            game.getCurrentLocation()->addVisibleObject(objectPtr);
            break;
        }
    }
}

void TUI::inspect(String item) {
    if (item == "Self") {
        log << "  Player stats:" << "\n";
        log << "  Health: " << player.getHealth() << "\n";
        log << "  Attack chance: " << player.getHitChancePercent() << "%" << "\n";
        log << "  Gold: " << player.getGold() << "\n";

        log << "\n";

        if (player.getEquippedWeapon() != nullptr) {
            log << "  Equipped weapon: " << player.getEquippedWeapon()->getName() << "\n";
        } else {
            log << "  Equipped weapon: None" << "\n";
        }
        if (player.getEquippedArmor() != nullptr) {
            log << "  Equipped armor: " << player.getEquippedArmor()->getName() << "\n";
        } else {
            log << "  Equipped armor: None" << "\n";
        }

        log << "\n";

        log << "  Inventory:" << "\n";
        for (int i = 0; i < player.getInventory().size(); i++) {
            log << "      " << player.getInventory()[i]->getName() << "\n";
        }
    } else {
        Vector<GameObject*>& currentVisibleObjects = game.getCurrentLocation()->getVisibleObjects();
        for (int i = 0; i < currentVisibleObjects.size(); i++) {
            if (currentVisibleObjects[i]->getName() == item) {
                log << currentVisibleObjects[i]->getName() << "\n";
                log << currentVisibleObjects[i]->getDescription() << "\n";
                if (currentVisibleObjects[i]->getMin() == 0 && currentVisibleObjects[i]->getMax() == 0) {
                    log << "Value: " << currentVisibleObjects[i]->getValue() << "\n";
                } else {
                    log << "Min: " << currentVisibleObjects[i]->getMin() << "\n";
                    log << "Max: " << currentVisibleObjects[i]->getMax() << "\n";
                }

                if (dynamic_cast<ArmorObject*>(currentVisibleObjects[i])) {
                    log << "Protection: " << currentVisibleObjects[i]->getValue() << "\n";
                }
                return;
            }
        }

        // check if item in player inventory
        // get player inventory and then loop through it
        std::vector<std::unique_ptr<GameObject>>& inventory = player.getInventory();
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i]->getName() == item) {
                log << inventory[i]->getName() << "\n";
                log << inventory[i]->getDescription() << "\n";
                if (inventory[i]->getMin() == 0 && inventory[i]->getMax() == 0) {
                    log << "Value: " << inventory[i]->getValue() << "\n";
                } else {
                    log << "Min: " << inventory[i]->getMin() << "\n";
                    log << "Max: " << inventory[i]->getMax() << "\n";
                }

                if (dynamic_cast<ArmorObject*>(inventory[i].get())) {
                    log << "Protection: " << inventory[i]->getValue() << "\n";
                }
                return;
            }
        }

        // check if item is equipped weapon or armor
        if (player.getEquippedWeapon() != nullptr && player.getEquippedWeapon()->getName() == item) {
            log << player.getEquippedWeapon()->getName() << "\n";
            log << player.getEquippedWeapon()->getDescription() << "\n";
            log << "Min: " << player.getEquippedWeapon()->getMin() << "\n";
            log << "Max: " << player.getEquippedWeapon()->getMax() << "\n";
            return;
        }

        if (player.getEquippedArmor() != nullptr && player.getEquippedArmor()->getName() == item) {
            log << player.getEquippedArmor()->getName() << "\n";
            log << player.getEquippedArmor()->getDescription() << "\n";
            log << "Protection: " << player.getEquippedArmor()->getValue() << "\n";
            return;
        }

        // check if item is name of enemy in current location
        Vector<Enemy*>& currentEnemies = game.getCurrentLocation()->getEnemies();
        for (int i = 0; i < currentEnemies.size(); i++) {
            if (currentEnemies[i]->getName() == item) {
                if (currentEnemies[i]->getHealth() == 0) {
                    log << "Defeated " << currentEnemies[i]->getName() << "\n";
                    log << currentEnemies[i]->getDescription() << "\n";
                    log << "Moving hidden items from enemy to visible objects in the location." << "\n";

                    // Move hidden items from enemy to visible objects in the location
                    while (currentEnemies[i]->getInventory().size() > 0) {
                        GameObject* object = currentEnemies[i]->getInventory()[0];
                        game.getCurrentLocation()->addVisibleObject(object);
                        currentEnemies[i]->removeObject(object);
                    }
                    return;
                } else {
                    log << currentEnemies[i]->getName() << "\n";
                    log << currentEnemies[i]->getDescription() << "\n";
                    log << "Health: " << currentEnemies[i]->getHealth() << "\n";
                    log << "Hit chance: " << currentEnemies[i]->getHitChancePercent() << "%" << "\n";
                    log << "Min damage: " << currentEnemies[i]->getMinDamage() << "\n";
                    log << "Max damage: " << currentEnemies[i]->getMaxDamage() << "\n";
                    return;
                }
            }
        }
    }
}

void TUI::attack(String enemy) {
    log << "Attacking " << enemy << "\n";

    Vector<Enemy*>& currentEnemies = game.getCurrentLocation()->getEnemies();
    for (int i = 0; i < currentEnemies.size(); i++) {
        if (currentEnemies[i]->getName() == enemy) {
            if (player.getEquippedWeapon() != nullptr) {
                if (Random::getInstance().generateIntInRange(0, 100) > player.getHitChancePercent()) {
                    log << "Missed attack." << "\n";
                    break;
                }
                int damage = Random::getInstance().generateIntInRange(player.getEquippedWeapon()->getMin(),
                                                                      player.getEquippedWeapon()->getMax());
                currentEnemies[i]->setHealth(currentEnemies[i]->getHealth() - damage);
                log << "Dealt " << damage << " damage to " << currentEnemies[i]->getName() << "\n";
                if (currentEnemies[i]->getHealth() <= 0) {
                    log << "Defeated " << currentEnemies[i]->getName() << "\n";
                    currentEnemies[i]->setHealth(0);
                }
            } else {
                log << "No weapon equipped." << "\n";
            }
            break;
        }
        if (i == currentEnemies.size() - 1) {
            log << "Enemy not found." << "\n";
        }
    }

    runEnemyTurns();
}

void TUI::equip(String item) {
    // check if item present in player inventory
    std::vector<std::unique_ptr<GameObject>>& inventory = player.getInventory();
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i]->getName() == item) {
            if (dynamic_cast<ArmorObject*>(inventory[i].get())) {
                player.setEquippedArmor(item);
                runEnemyTurns();
                return;
            } else if (dynamic_cast<WeaponObject*>(inventory[i].get())) {
                player.setEquippedWeapon(item);
                return;
            }
        }
    }

    log << "Equipping " << item << "\n";
}

void TUI::wait() {
    log << "Waiting..." << "\n";

    runEnemyTurns();
}

void TUI::consume(String item) {
    log << "Consuming " << item << "\n";

    std::vector<std::unique_ptr<GameObject>>& inventory = player.getInventory();
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i]->getName() == item) {
            if (dynamic_cast<HealthPotionObject*>(inventory[i].get())) {
                int healthRestored =
                    Random::getInstance().generateIntInRange(inventory[i]->getMin(), inventory[i]->getMax());
                player.setHealth(player.getHealth() + healthRestored);
                log << "Restored " << healthRestored << " health points." << "\n";
                player.removeObject(inventory[i]);
                return;
            } else if (dynamic_cast<ExperiencePotionObject*>(inventory[i].get())) {
                int hitChancePercent = player.getHitChancePercent();
                if (hitChancePercent < 90) {
                    player.setHitChancePercent(hitChancePercent + Random::getInstance().generateIntInRange(
                                                                      inventory[i]->getMin(), inventory[i]->getMax()));
                    log << "Increased attack chance" << "\n";

                    player.removeObject(inventory[i]);
                } else {
                    log << "Attack chance already at maximum." << "\n";
                }
                return;
            } else if (dynamic_cast<TeleportationPotionObject*>(inventory[i].get())) {
                log << "Teleporting to a random location." << "\n";
                game.setNewCurrentLocation(Random::getInstance().generateIntInRange(0, game.amountOfLocations() - 1));
                player.removeObject(inventory[i]);
                return;
            } else {
                log << "Consumed " << item << "\n";
                return;
            }
        }
    }

    return;
}

void TUI::godmode() {
    log << "God mode activated!" << "\n";

    player.setHealth(99999999);
    player.setHitChancePercent(100);
}

void TUI::createGameFromFile() {
    LocationParser parser(xmlFilename);
    std::vector<Location*> locations = parser.parse();
    Vector<Location*> newLocations;

    for (int i = 0; i < locations.size(); i++) {
        newLocations.push_back(locations[i]);
    }

    game.setLocations(newLocations);
}

void TUI::printHelp() {
    log << "  Available Actions:\n";
    log << "  Look : Shows the location's description with visible objects, all possible exits, and any enemies "
           "present.\n";
    log << "  Search* : Moves hidden objects in the current location to visible objects, except those associated "
           "with enemies here.\n";
    log << "  Go <north|south|east|west>* : If there's an exit in the chosen direction, move there. If enemies are "
           "present, they each attack once before moving.\n";
    log << "  Take <OBJECT> : Moves a visible object from the location to the player. For 'gold coins', add to the "
           "player’s total and delete the object.\n";
    log << "  Drop <OBJECT> : Moves an object from the player to visible objects in the current location.\n";
    log << "  Inspect <OBJECT> : Shows description of the object if visible in the location or held by the "
           "player.\n";
    log << "  Inspect <ENEMY> :\n";
    log << "    If enemy has health: Shows the enemy's description (if present in the location).\n";
    log << "    If enemy has 0 health: Shows the description, and moves hidden items from the enemy to visible "
           "objects in the location.\n";
    log << "  Inspect Self : Displays player stats: health, attack chance, gold, equipped weapon, armor, and "
           "inventory.\n";
    log << "  Attack <ENEMY>* : Attack the specified enemy with the equipped weapon.\n";
    log << "  Equip <OBJECT:ARMOR>* : If player owns the armor, equip it. Previously worn armor becomes a visible "
           "object in the location.\n";
    log << "  Equip <OBJECT:WEAPON> : If player owns the weapon, equip it. Previously held weapon becomes a "
           "visible object in the location.\n";
    log << "  Wait* : Skip the turn. Enemies may attack and move.\n";
    log << "  Consume <OBJECT:CONSUMABLE> : Effects vary based on potion type:\n";
    log << "    Health Elixir: Restores 5-15 health points.\n";
    log << "    Experience Potion: Increases attack chance by +10%, up to 90% max.\n";
    log << "    Teleportation Potion: Teleports player to a random location.\n";
    log << "  Help : Shows this list of available actions.\n";
    log << "  Godmode : Toggles 'godmode' where player cannot lose health or miss attacks.\n";
    log << "  Quit : Ends the game and closes the application properly to reveal any memory leaks.\n";
    log << "\n* Indicates an action that ends the player's turn.\n";
}

void TUI::runEnemyTurns() {
    // retrieve enemies from current location
    Vector<Enemy*>& currentEnemies = game.getCurrentLocation()->getEnemies();
    for (int i = 0; i < currentEnemies.size(); i++) {
        // check if enemy has health
        if (currentEnemies[i]->getHealth() > 0) {
            // enemy attacks player
            if (Random::getInstance().generateIntInRange(0, 100) > currentEnemies[i]->getHitChancePercent()) {
                log << currentEnemies[i]->getName() << " missed attack." << "\n";
            } else {
                int damage = Random::getInstance().generateIntInRange(currentEnemies[i]->getMinDamage(),
                                                                      currentEnemies[i]->getMaxDamage());
                damage =
                    (player.getEquippedArmor() != nullptr) ? damage - player.getEquippedArmor()->getValue() : damage;

                if (damage < 0) {
                    damage = 0;
                }

                player.setHealth(player.getHealth() - damage);
                log << currentEnemies[i]->getName() << " dealt " << damage << " damage to player." << "\n";

                if (player.getHealth() <= 0) {
                    log << "Player has died." << "\n";
                    return;
                }
            }
        }
    }
}

String TUI::getInput() {
    char buffer[1024]; // Temporary buffer for input

    std::cin.getline(buffer, sizeof(buffer)); // Read a line from input into buffer

    String input = buffer; // Convert buffer to String

    return input;
}
