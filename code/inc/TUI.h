#ifndef TUI_H
#define TUI_H

#include "Game.h"
#include "Log.h"
#include "Player.h"
#include "String.h"

class TUI {
public:
    TUI();
    TUI(std::string filename);
    ~TUI();

    void init();
    void endOfGame();
    void startup();
    bool run();

private:
    void printPrompt();
    void handleInput();

    void printHelp();

    void look(String item);
    void search(String item);
    void go(String direction);
    void take(String item);
    void drop(String item);
    void inspect(String item);
    void attack(String enemy);
    void equip(String item);
    void wait();
    void consume(String item);
    void godmode();
    void suicide();

    void createGameFromFile();

    // void printStats();
    // void printInventory();
    // void printMap();
    // void printLocation();
    // void printEnemies();
    // void printItems();

    // void clearScreen();
    // void moveCursor(int x, int y);

private:
    String getInput();

    void addScoreToDB();
    void displayHighScores();
    void runEnemyTurns();

private:
    Log log;
    Game game;
    Player player;

    std::string xmlFilename = "";
    bool running;
    bool restart;
};

#endif // TUI_H
