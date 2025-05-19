#pragma once
#include <cppconn/connection.h>

class Database {
public:
    static sql::Connection* getConnection();
};
