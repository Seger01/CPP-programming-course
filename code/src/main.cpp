#include "Database.h"
#include "GameObjectFactory.h"
#include <iostream>

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
    GameObject* armorObject = GameObjectFactory::instance().createProduct("ArmorObject");

    if (armorObject) {
        delete armorObject;
    }
    //
    // Database db("kerkersendraken.db");
    //
    // if (!db.open()) {
    //     return -1;
    // }
    //
    // // Query the table
    // MyVector<MyVector<MyString>> results; // Using custom vector for results
    // const char* selectSQL = "SELECT * FROM Objecten;";
    // if (db.executeQuery(selectSQL, results)) {
    //     std::cout << "Query results:" << std::endl;
    //     for (size_t i = 0; i < results.size(); ++i) {
    //         for (size_t j = 0; j < results[i].size(); ++j) {
    //             std::cout << results[i][j] << " "; // Use custom String
    //         }
    //         std::cout << std::endl;
    //     }
    // }
    //
    // db.close();

    // // test 2d vector of my vector of my string
    // MyVector<MyVector<MyString>> results;
    // MyVector<MyString> row1;
    // row1.push_back(MyString("Hello"));
    // row1.push_back(MyString("World"));
    // results.push_back(row1);

    MyVector<MyVector<MyString>> cols;

    MyString string = MyString("Hello");

    string = "wat de fuk";

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 5; j++) {
            MyVector<MyString> row;
            row.push_back(MyString("Hello"));
            row.push_back(MyString("World"));

            if (row[0].length() != 5) {
                std::cout << "Length is not 5" << std::endl;
            }
            if (row[1].length() != 5) {
                std::cout << "Length is not 5" << std::endl;
            }

            cols.push_back(row);
        }
    }

    std::cout << "Size of cols: " << cols.size() << std::endl;

    for (size_t i = 0; i < cols.size(); ++i) {
        std::cout << "Cols size: " << cols[i].size() << std::endl;
        for (size_t j = 0; j < cols[i].size(); ++j) {
            std::cout << cols[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
