#include "TUI.h"

#include <iostream>
#include <memory>

#include "ArmorObject.h"
#include "Enemy.h"
#include "ExperiencePotionObject.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "HealthPotionObject.h"
#include "Random.h"
#include "String.h"
#include "TeleportationPotionObject.h"
#include "WeaponObject.h"

TUI::TUI() {
    running = false;

    game = Game();
    game.start();
    int amountOfRooms = 10;
    game.generateDungeon(amountOfRooms);

    player = Player();
    Vector<Vector<String>> objectInfo = game.getObjectInfo();

    int dolkIndex = -1;
    for (int i = 0; i < objectInfo.size(); i++) {
        if (objectInfo[i][0] == "dolk") {
            dolkIndex = i;
            break;
        }
    }

    GameObject* object = GameObjectFactory::instance().createObject(objectInfo[dolkIndex][2]);

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

    object->setData(objectName, objectDescription, objectMin, objectMax, objectProtection);

    player.addObject(std::unique_ptr<GameObject>(object));
    player.setEquippedWeapon(object->getName());
}

TUI::~TUI() {}

void TUI::run() {
    std::cout << "Welcome to Kerkers en Draken!" << std::endl;
    std::cout << "Type 'Help' for a list of commands." << std::endl;

    running = true;

    while (running) {
        printPrompt();
        handleInput();
    }
}

void TUI::printPrompt() { std::cout << " > "; }

void TUI::handleInput() {
    String input = getInput();

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
    } else if (action == "Godmode") {
        godmode();
    } else if (action == "Quit") {
        running = false;
    } else {
    }
}

void TUI::look(String item) {
    Location* currentLocation = game.getCurrentLocation();
    if (currentLocation == nullptr) {
        return;
    }

    std::cout << "Location: " << currentLocation->getName() << std::endl;
    std::cout << "Description: " << currentLocation->getDescription() << std::endl;
    std::cout << std::endl;

    std::cout << "Visible objects:" << std::endl;
    for (int i = 0; i < currentLocation->getVisibleObjects().size(); i++) {
        std::cout << currentLocation->getVisibleObjects()[i]->getName() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Exits:" << std::endl;
    for (int i = 0; i < currentLocation->getExits().size(); i++) {
        if (currentLocation->getExits()[i] != -1) {
            switch (i) {
            case 0:
                std::cout << "North" << std::endl;
                break;
            case 1:
                std::cout << "East" << std::endl;
                break;
            case 2:
                std::cout << "South" << std::endl;
                break;
            case 3:
                std::cout << "West" << std::endl;
                break;
            }
        }
    }
    std::cout << std::endl;

    std::cout << "Enemies:" << std::endl;
    for (int i = 0; i < currentLocation->getEnemies().size(); i++) {
        std::cout << currentLocation->getEnemies()[i]->getName() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Hidden objects:" << std::endl;
    for (int i = 0; i < currentLocation->getHiddenObjects().size(); i++) {
        std::cout << currentLocation->getHiddenObjects()[i]->getName() << std::endl;
    }
    std::cout << std::endl;
}

void TUI::search(String item) {
    std::cout << "Searched" << item << std::endl;

    while (game.getCurrentLocation()->getHiddenObjects().size() > 0) {
        GameObject* object = game.getCurrentLocation()->getHiddenObjects()[0];
        game.getCurrentLocation()->addVisibleObject(object);
        game.getCurrentLocation()->removeHiddenObject(object);
    }

    return;
}

void TUI::go(String direction) {
    if (direction == "North") {
        if (game.getCurrentLocation()->getExits()[0] != -1) {
            game.setNewCurrentLocation(game.getCurrentLocation()->getExits()[0]);
        }
    } else if (direction == "East") {
        if (game.getCurrentLocation()->getExits()[1] != -1) {
            game.setNewCurrentLocation(game.getCurrentLocation()->getExits()[1]);
        }
    } else if (direction == "South") {
        if (game.getCurrentLocation()->getExits()[2] != -1) {
            game.setNewCurrentLocation(game.getCurrentLocation()->getExits()[2]);
        }
    } else if (direction == "West") {
        if (game.getCurrentLocation()->getExits()[3] != -1) {
            game.setNewCurrentLocation(game.getCurrentLocation()->getExits()[3]);
        }
    } else {
        std::cout << "Invalid direction." << std::endl;
    }
}

void TUI::take(String item) {
    std::cout << "Taking " << item << std::endl;

    std::unique_ptr<GameObject> gameObject(game.takeObject(item));

    if (gameObject != nullptr) {
        std::cout << "Adding " << gameObject->getName() << " to inventory." << std::endl;
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
        std::cout << "  Player stats:" << std::endl;
        std::cout << "  Health: " << player.getHealth() << std::endl;
        std::cout << "  Attack chance: " << player.getHitChancePercent() << "%" << std::endl;
        std::cout << "  Gold: " << player.getGold() << std::endl;

        std::cout << std::endl;

        if (player.getEquippedWeapon() != nullptr) {
            std::cout << "  Equipped weapon: " << player.getEquippedWeapon()->getName() << std::endl;
        } else {
            std::cout << "  Equipped weapon: None" << std::endl;
        }
        if (player.getEquippedArmor() != nullptr) {
            std::cout << "  Equipped armor: " << player.getEquippedArmor()->getName() << std::endl;
        } else {
            std::cout << "  Equipped armor: None" << std::endl;
        }

        std::cout << std::endl;

        std::cout << "  Inventory:" << std::endl;
        for (int i = 0; i < player.getInventory().size(); i++) {
            std::cout << "      " << player.getInventory()[i]->getName() << std::endl;
        }
    } else {
        Vector<GameObject*>& currentVisibleObjects = game.getCurrentLocation()->getVisibleObjects();
        for (int i = 0; i < currentVisibleObjects.size(); i++) {
            if (currentVisibleObjects[i]->getName() == item) {
                std::cout << currentVisibleObjects[i]->getName() << std::endl;
                std::cout << currentVisibleObjects[i]->getDescription() << std::endl;
                if (currentVisibleObjects[i]->getMin() == 0 && currentVisibleObjects[i]->getMax() == 0) {
                    std::cout << "Value: " << currentVisibleObjects[i]->getValue() << std::endl;
                } else {
                    std::cout << "Min: " << currentVisibleObjects[i]->getMin() << std::endl;
                    std::cout << "Max: " << currentVisibleObjects[i]->getMax() << std::endl;
                }

                if (dynamic_cast<ArmorObject*>(currentVisibleObjects[i])) {
                    std::cout << "Protection: " << currentVisibleObjects[i]->getValue() << std::endl;
                }
                return;
            }
        }

        // check if item in player inventory
        // get player inventory and then loop through it
        std::vector<std::unique_ptr<GameObject>>& inventory = player.getInventory();
        for (int i = 0; i < inventory.size(); i++) {
            if (inventory[i]->getName() == item) {
                std::cout << inventory[i]->getName() << std::endl;
                std::cout << inventory[i]->getDescription() << std::endl;
                if (inventory[i]->getMin() == 0 && inventory[i]->getMax() == 0) {
                    std::cout << "Value: " << inventory[i]->getValue() << std::endl;
                } else {
                    std::cout << "Min: " << inventory[i]->getMin() << std::endl;
                    std::cout << "Max: " << inventory[i]->getMax() << std::endl;
                }

                if (dynamic_cast<ArmorObject*>(inventory[i].get())) {
                    std::cout << "Protection: " << inventory[i]->getValue() << std::endl;
                }
                return;
            }
        }

        // check if item is equipped weapon or armor
        if (player.getEquippedWeapon() != nullptr && player.getEquippedWeapon()->getName() == item) {
            std::cout << player.getEquippedWeapon()->getName() << std::endl;
            std::cout << player.getEquippedWeapon()->getDescription() << std::endl;
            std::cout << "Min: " << player.getEquippedWeapon()->getMin() << std::endl;
            std::cout << "Max: " << player.getEquippedWeapon()->getMax() << std::endl;
            return;
        }

        if (player.getEquippedArmor() != nullptr && player.getEquippedArmor()->getName() == item) {
            std::cout << player.getEquippedArmor()->getName() << std::endl;
            std::cout << player.getEquippedArmor()->getDescription() << std::endl;
            std::cout << "Protection: " << player.getEquippedArmor()->getValue() << std::endl;
            return;
        }

        // check if item is name of enemy in current location
        Vector<Enemy*>& currentEnemies = game.getCurrentLocation()->getEnemies();
        for (int i = 0; i < currentEnemies.size(); i++) {
            if (currentEnemies[i]->getName() == item) {
                if (currentEnemies[i]->getHealth() == 0) {
                    std::cout << currentEnemies[i]->getName() << std::endl;
                    std::cout << currentEnemies[i]->getDescription() << std::endl;
                    std::cout << "Moving hidden items from enemy to visible objects in the location." << std::endl;

                    // Move hidden items from enemy to visible objects in the location
                    while (currentEnemies[i]->getInventory().size() > 0) {
                        GameObject* object = currentEnemies[i]->getInventory()[0];
                        game.getCurrentLocation()->addVisibleObject(object);
                        currentEnemies[i]->removeObject(object);
                    }
                    return;
                } else {
                    std::cout << currentEnemies[i]->getName() << std::endl;
                    std::cout << currentEnemies[i]->getDescription() << std::endl;
                    std::cout << "Health: " << currentEnemies[i]->getHealth() << std::endl;
                    std::cout << "Hit chance: " << currentEnemies[i]->getHitChancePercent() << "%" << std::endl;
                    std::cout << "Min damage: " << currentEnemies[i]->getMinDamage() << std::endl;
                    std::cout << "Max damage: " << currentEnemies[i]->getMaxDamage() << std::endl;
                    return;
                }
            }
        }
    }
}

void TUI::attack(String enemy) {
    std::cout << "Attacking " << enemy << std::endl;

    Vector<Enemy*>& currentEnemies = game.getCurrentLocation()->getEnemies();
    for (int i = 0; i < currentEnemies.size(); i++) {
        if (currentEnemies[i]->getName() == enemy) {
            if (player.getEquippedWeapon() != nullptr) {
                if (Random::getInstance().generateIntInRange(0, 100) > player.getHitChancePercent()) {
                    std::cout << "Missed attack." << std::endl;
                    return;
                }
                int damage = Random::getInstance().generateIntInRange(player.getEquippedWeapon()->getMin(),
                                                                      player.getEquippedWeapon()->getMax());
                currentEnemies[i]->setHealth(currentEnemies[i]->getHealth() - damage);
                std::cout << "Dealt " << damage << " damage to " << currentEnemies[i]->getName() << std::endl;
                if (currentEnemies[i]->getHealth() <= 0) {
                    std::cout << "Defeated " << currentEnemies[i]->getName() << std::endl;
                    currentEnemies[i]->setHealth(0);
                    // while (currentEnemies[i]->getInventory().size() > 0) {
                    //     GameObject* object = currentEnemies[i]->getInventory()[0];
                    //     game.getCurrentLocation()->addVisibleObject(object);
                    //     currentEnemies[i]->removeObject(object);
                    // }
                }
            } else {
                std::cout << "No weapon equipped." << std::endl;
            }
            return;
        }
    }

    std::cout << "Enemy not found." << std::endl;
}

void TUI::equip(String item) {
    // check if item present in player inventory
    std::vector<std::unique_ptr<GameObject>>& inventory = player.getInventory();
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i]->getName() == item) {
            if (dynamic_cast<ArmorObject*>(inventory[i].get())) {
                player.setEquippedArmor(item);
                return;
            } else if (dynamic_cast<WeaponObject*>(inventory[i].get())) {
                player.setEquippedWeapon(item);
                return;
            }
        }
    }

    std::cout << "Equipping " << item << std::endl;
}

void TUI::wait() {
    std::cout << "Waiting..." << std::endl;

    game.runEnemyTurns();
}

void TUI::consume(String item) {
    std::cout << "Consuming " << item << std::endl;

    std::vector<std::unique_ptr<GameObject>>& inventory = player.getInventory();
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i]->getName() == item) {
            if (dynamic_cast<HealthPotionObject*>(inventory[i].get())) {
                int healthRestored =
                    Random::getInstance().generateIntInRange(inventory[i]->getMin(), inventory[i]->getMax());
                player.setHealth(player.getHealth() + healthRestored);
                std::cout << "Restored " << healthRestored << " health points." << std::endl;
                return;
            } else if (dynamic_cast<ExperiencePotionObject*>(inventory[i].get())) {
                int hitChancePercent = player.getHitChancePercent();
                if (hitChancePercent < 90) {
                    player.setHitChancePercent(hitChancePercent + Random::getInstance().generateIntInRange(
                                                                      inventory[i]->getMin(), inventory[i]->getMax()));
                    std::cout << "Increased attack chance" << std::endl;
                } else {
                    std::cout << "Attack chance already at maximum." << std::endl;
                }
                return;
            } else if (dynamic_cast<TeleportationPotionObject*>(inventory[i].get())) {
                std::cout << "Teleporting to a random location." << std::endl;
                game.setNewCurrentLocation(Random::getInstance().generateIntInRange(0, game.amountOfLocations() - 1));
                return;
            } else {
                std::cout << "Consumed " << item << std::endl;
                return;
            }
        }
    }

    return;
}

void TUI::godmode() {
    std::cout << "God mode activated!" << std::endl;

    player.setHealth(99999999);
    player.setHitChancePercent(100);
}

void TUI::printHelp() {
    std::cout << "  Available Actions:\n";
    std::cout << "  Look : Shows the location's description with visible objects, all possible exits, and any enemies "
                 "present.\n";
    std::cout << "  Search* : Moves hidden objects in the current location to visible objects, except those associated "
                 "with enemies here.\n";
    std::cout
        << "  Go <north|south|east|west>* : If there's an exit in the chosen direction, move there. If enemies are "
           "present, they each attack once before moving.\n";
    std::cout
        << "  Take <OBJECT> : Moves a visible object from the location to the player. For 'gold coins', add to the "
           "player’s total and delete the object.\n";
    std::cout << "  Drop <OBJECT> : Moves an object from the player to visible objects in the current location.\n";
    std::cout << "  Inspect <OBJECT> : Shows description of the object if visible in the location or held by the "
                 "player.\n";
    std::cout << "  Inspect <ENEMY> :\n";
    std::cout << "    If enemy has health: Shows the enemy's description (if present in the location).\n";
    std::cout << "    If enemy has 0 health: Shows the description, and moves hidden items from the enemy to visible "
                 "objects in the location.\n";
    std::cout << "  Inspect Self : Displays player stats: health, attack chance, gold, equipped weapon, armor, and "
                 "inventory.\n";
    std::cout << "  Attack <ENEMY>* : Attack the specified enemy with the equipped weapon.\n";
    std::cout
        << "  Equip <OBJECT:ARMOR>* : If player owns the armor, equip it. Previously worn armor becomes a visible "
           "object in the location.\n";
    std::cout << "  Equip <OBJECT:WEAPON> : If player owns the weapon, equip it. Previously held weapon becomes a "
                 "visible object in the location.\n";
    std::cout << "  Wait* : Skip the turn. Enemies may attack and move.\n";
    std::cout << "  Consume <OBJECT:CONSUMABLE> : Effects vary based on potion type:\n";
    std::cout << "    Health Elixir: Restores 5-15 health points.\n";
    std::cout << "    Experience Potion: Increases attack chance by +10%, up to 90% max.\n";
    std::cout << "    Teleportation Potion: Teleports player to a random location.\n";
    std::cout << "  Help : Shows this list of available actions.\n";
    std::cout << "  Godmode : Toggles 'godmode' where player cannot lose health or miss attacks.\n";
    std::cout << "  Quit : Ends the game and closes the application properly to reveal any memory leaks.\n";
    std::cout << "\n* Indicates an action that ends the player's turn.\n";
}

String TUI::getInput() {
    char buffer[1024]; // Temporary buffer for input

    std::cin.getline(buffer, sizeof(buffer)); // Read a line from input into buffer

    String input = buffer; // Convert buffer to String

    return input;
}
