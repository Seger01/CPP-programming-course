#ifndef DATABASE_H
#define DATABASE_H

#include "String.h"
#include "Vector.h"
#include <iostream>
#include <sqlite3.h>

class Database {
public:
    Database(String dbName); // Use custom String
    ~Database();

    bool open();
    void close();
    bool execute(const char* sql);
    bool executeQuery(const char* sql, Vector<Vector<String>>& results); // Use custom String

private:
    String dbName; // Use custom String
    sqlite3* db;
};

#endif // DATABASE_H
