#ifndef SQLITE_CONNECTION_H

#define SQLITE_CONNECTION_H

#include "sqlite3.h"

#include <string>

class SqliteConnection final
{
    public:

    explicit SqliteConnection(const std::string& fileLocation);

    ~SqliteConnection();

    /**
     * get opened connection or nullptr if it is not opened
     * 
     */
    sqlite3* getConnection() const;

    bool exec(const std::string& sql);
    
    private:

    void open(const std::string& fileLocation);

    void close();

    private:

    sqlite3* pdatabase;

};

#endif