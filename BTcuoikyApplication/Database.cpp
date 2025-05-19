#include "Database.h"
#include <mysql_connection.h>
#include <mysql_driver.h>

//const std::string server = "sql12.freesqldatabase.com";
//const std::string username = "sql12778161";
//const std::string password = "C6dmKbY7Lk";
//const std::string schema = "sql12778161";

const std::string server = "localhost:3306";
const std::string username = "root";
const std::string password = "root";
const std::string schema = "application_account_manager_db";

sql::Connection* Database::getConnection() {
    sql::Driver* driver = get_driver_instance();
    sql::Connection* con = driver->connect(server, username, password);
    con->setSchema(schema);
    return con;
}