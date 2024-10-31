#include "TUI.h"

#include <iostream>

#include "String.h"

TUI::TUI() {
    running = false;

    game = Game();
}

TUI::~TUI() {}

void TUI::run() {
    std::cout << "Welcome to Kerkers en Draken!" << std::endl;
    std::cout << "Type 'Help' for a list of commands." << std::endl;

    running = true;

    int amountOfRooms = 10;

    game.generateDungeon(amountOfRooms);

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
    } else if (action == "Grab") {
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

void TUI::look(String item) { std::cout << "Looking at " << item << std::endl; }

void TUI::search(String item) { std::cout << "Searching for " << item << std::endl; }

void TUI::go(String direction) { std::cout << "Going " << direction << std::endl; }

void TUI::take(String item) { std::cout << "Taking " << item << std::endl; }

void TUI::drop(String item) { std::cout << "Dropping " << item << std::endl; }

void TUI::inspect(String item) { std::cout << "Inspecting " << item << std::endl; }

void TUI::attack(String enemy) { std::cout << "Attaking " << enemy << std::endl; }

void TUI::equip(String item) { std::cout << "Equipping " << item << std::endl; }

void TUI::wait() { std::cout << "Waiting..." << std::endl; }

void TUI::consume(String item) { std::cout << "Consuming " << item << std::endl; }

void TUI::godmode() { std::cout << "God mode activated!" << std::endl; }

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
    std::cout
        << "    Inspect <OBJECT> : Shows description of the object if visible in the location or held by the player.\n";
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
    std::cout << "\n* indicates actions that may have restrictions depending on the game state.\n";
}

String TUI::getInput() {
    char buffer[1024]; // Temporary buffer for input

    std::cin.getline(buffer, sizeof(buffer)); // Read a line from input into buffer

    String input = buffer; // Convert buffer to String

    return input;
}
