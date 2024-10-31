#include <iostream>

#include <cstring>
#include <string>

#include "Database.h"
#include "GameObjectFactory.h"
#include "String.h"
#include "TUI.h"
#include "Vector.h"

// main function with input args and return type int the one input argument is a
// file path
int main(int argc, char* argv[]) {
    // check if the input argument is not provided
    // if (argc < 2) {
    //     // print the error message
    //     std::cerr << "Usage: " << argv[0] << " FILE_PATH" << std::endl;
    //     // return 1 to indicate the error
    //     return 1;
    // }
    //
    // // print the file path
    // std::cout << "File path: " << argv[1] << std::endl;

    // Create products using the factory
    // GameObject* armorObject = GameObjectFactory::instance().createProduct("ArmorObject");
    //
    // if (armorObject) {
    //     delete armorObject;
    // }
    //
    // Database db("kerkersendraken.db");
    //
    // if (!db.open()) {
    //     return -1;
    // }
    //
    // // Query the table
    // Vector<Vector<String>> results; // Using custom vector for results
    // const char* selectSQL = "SELECT * FROM Objecten;";
    // if (db.executeQuery(selectSQL, results)) {
    //     std::cout << "Query results:" << std::endl;
    //     for (size_t i = 0; i < results.size(); ++i) {
    //         for (size_t j = 0; j < results[i].size(); ++j) {
    //             std::cout << results[i][j] << results[i][j].length() << " "; // Use custom String
    //         }
    //         std::cout << std::endl;
    //     }
    // }
    //
    // db.close();

    TUI tui;

    tui.run();

    return 0;
}
