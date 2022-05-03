#ifndef SQLDATABASE_H
#define SQLDATABASE_H
#include <mariadb/conncpp.hpp>
#include <iostream>

class SQLDatabase
{
private:
    std::unique_ptr<sql::Connection> conn;
    sql::Driver* driver;

    sql::SQLString def_url = "jdbc:mariadb://192.168.0.11:3306/UBRP";

    std::string def_user = "ubrp";
    std::string def_pass = "qwerty";
    sql::Properties properties = {
          {"user", def_user.c_str()},
          {"password", def_pass.c_str()}
       };
public:
    SQLDatabase();
    void try_connect(sql::SQLString url);
    int SQLInsert(const char* date_connected, const char* host, const char* vendor_id, const char* product_id, const char* manufacturer,
                  const char* serial, const char* product, const char* port, const char* date_disconnected);
    const char* SQLSelect();
    bool SQLIsConnected();
    sql::SQLString get_url();
    std::string get_sql_user();
    std::string get_sql_pass();
    void set_sql_user(std::string user);
    void set_sql_pass(std::string pass);
    void set_properties(std::string user, std::string pass);
    void set_url(sql::SQLString url);
    ~SQLDatabase();
};

#endif // SQLDATABASE_H
