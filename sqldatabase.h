#ifndef SQLDATABASE_H
#define SQLDATABASE_H
#include <conncpp.hpp>
#include <iostream>

class SQLDatabase
{
private:
    std::unique_ptr<sql::Connection> conn;
public:
    SQLDatabase();
    int SQLInsert(const char* date_connected, const char* host, const char* vendor_id, const char* product_id, const char* manufacturer,
                  const char* serial, const char* product, const char* port, const char* date_disconnected);
    const char* SQLSelect();
    ~SQLDatabase();
};

#endif // SQLDATABASE_H
