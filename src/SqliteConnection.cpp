#include "SqliteConnection.h"

#include <iostream>

SqliteConnection::SqliteConnection(const std::string& fileLocation)
:pdatabase{nullptr}
{
    open(fileLocation);
}

SqliteConnection::~SqliteConnection()
{
    close();
}

sqlite3* SqliteConnection::getConnection() const
{
    return pdatabase;
}

bool SqliteConnection::exec(const std::string& sql)
{
    if(!pdatabase){
        return false;
    }

    return sqlite3_exec(pdatabase,
    sql.c_str(),
    nullptr,
    nullptr,
    nullptr)==SQLITE_OK;
}


void SqliteConnection::open(const std::string& fileLocation)
{
    if(sqlite3_open(fileLocation.c_str(),&pdatabase)!=SQLITE_OK){
        pdatabase = nullptr;

    }
}

void SqliteConnection::close()
{
    if(pdatabase){
        sqlite3_close(pdatabase);
    }
}