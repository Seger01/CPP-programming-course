#ifndef DATABASE_H
#define DATABASE_H

#include "MyString.h"
#include "MyVector.h"
#include <iostream>
#include <sqlite3.h>

class Database {
public:
    Database(const char* dbName);
    ~Database();

    bool open();
    void close();
    bool execute(const char* sql);
    bool executeQuery(const char* sql, MyVector<MyVector<MyString>>& results); // Use custom String

private:
    MyString dbName; // Use custom String
    sqlite3* db;
};

#endif // DATABASE_H
