#include "Database.h"
#include "String.h"
#include <cstring>

Database::Database(String dbName) : db(nullptr), dbName(dbName) {}

Database::~Database() { close(); }

bool Database::open() {
    if (sqlite3_open(dbName.c_str(), &db) == SQLITE_OK) {
        return true;
    } else {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
}

void Database::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::execute(const char* sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) == SQLITE_OK) {
        return true;
    } else {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
}

bool Database::executeQuery(const char* sql, Vector<Vector<String>>& results) {
    char* errMsg = nullptr;
    char** resultTable = nullptr;
    int rows, cols;

    if (sqlite3_get_table(db, sql, &resultTable, &rows, &cols, &errMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_free_table(resultTable);
        return false;
    }

    // Populate results vector
    for (int row = 1; row <= rows; ++row) {
        Vector<String> rowData;
        for (int col = 0; col < cols; ++col) {
            const char* cellValue = resultTable[(row * cols) + col];
            rowData.push_back(String(cellValue ? cellValue : "NULL")); // Use custom String
        }
        results.push_back(rowData);
    }

    sqlite3_free_table(resultTable);
    return true;
}
