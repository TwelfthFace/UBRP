#include "sqldatabase.h"

SQLDatabase::SQLDatabase()
{
    SQLDatabase::try_connect(SQLDatabase::def_url);
}

void SQLDatabase::try_connect(sql::SQLString url){
    try{
        SQLDatabase::driver = sql::mariadb::get_driver_instance();
        SQLDatabase::conn = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
    } catch (sql::SQLException &e) {
        std::cerr << "Invalid database connection... " << e.what() << std::endl;
        conn.reset();
    }
}

int SQLDatabase::SQLInsert(const char* date_connected, const char* host, const char* vendor_id, const char* product_id, const char* product, const char* manufacturer,
                       const char* serial, const char* port, const char* date_disconnected)
{
    std::shared_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO UBRP.Devices(date_connected, host, vendor_id, product_id,"
                                                                         "product, manufacturer, serial_number,"
                                                                         "port_identity, date_disconnect) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);"));

    try {
       stmnt->setString(1, date_connected);
       stmnt->setString(2, host);
       stmnt->setString(3, vendor_id);
       stmnt->setString(4, product_id);
       stmnt->setString(5, product);
       stmnt->setString(6, manufacturer);
       stmnt->setString(7, serial);
       stmnt->setString(8, port);
       stmnt->setString(9, date_disconnected);

       stmnt->executeUpdate();
    }

    catch (sql::SQLException &e) {
        std::cerr << "Error adding contact to database: "
            << e.what() << std::endl;
        return 1;
    }

    return 0;
}

const char* SQLDatabase::SQLSelect(){
    std::shared_ptr<sql::Statement> stmnt(conn->createStatement());

    std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery("SELECT * FROM UBRP.Devices"));

    std::string records;

    try{
        while (res->next()) {
            records+= "Record ID: ";
            records+= res->getString("device_id").append("\n");
            records+= "Date Connected: ";
            records+= res->getString("date_connected").append("\n");
            records+= "Host: ";
            records+= res->getString("host").append("\n");
            records+= "Vendor ID: ";
            records+= res->getString("vendor_id").append("\n");
            records+= "Product ID: ";
            records+= res->getString("product_id").append("\n");
            records+= "Product Name: ";
            records+= res->getString("product").append("\n");
            records+= "Manufacturer: ";
            records+= res->getString("manufacturer").append("\n");
            records+= "Serial Number: ";
            records+= res->getString("serial_number").append("\n");
            records+= "Port Number: ";
            records+= res->getString("port_identity").append("\n");
            records+= "Date Disconnected: ";
            records+= res->getString("date_disconnect").append("\n");
            records+= "\n";
        }
        return records.c_str();
    }catch (sql::SQLException& e) {
       std::cerr << "Error printing contacts: "
          << e.what() << std::endl;
    }
}

bool SQLDatabase::SQLIsConnected(){
    if(SQLDatabase::conn){
        return true;
    }

    return false;
}

sql::SQLString SQLDatabase::get_url(){
    return SQLDatabase::def_url;
}

std::string SQLDatabase::get_sql_pass(){
    return SQLDatabase::def_pass;
}

std::string SQLDatabase::get_sql_user(){
    return SQLDatabase::def_user;
}

void SQLDatabase::set_sql_user(std::string user){
    SQLDatabase::def_user = user;
}

void SQLDatabase::set_sql_pass(std::string pass){
    SQLDatabase::def_pass = pass;
}

void SQLDatabase::set_url(sql::SQLString url){
    SQLDatabase::def_url = url;
}

SQLDatabase::~SQLDatabase(){
    if(SQLDatabase::conn){
        conn->close();
    }
}

void SQLDatabase::set_properties(std::string user, std::string pass){
    SQLDatabase::properties = {
        {"user", user.c_str()},
        {"password", pass.c_str()}
     };
}
