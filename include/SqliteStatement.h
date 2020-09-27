#ifndef SQLITE_STATEMENT_H

#define SQLITE_STATEMENT_H


#include "sqlite3.h"

#include <string>

class SqliteConnection;

class SqliteStatement final
{
    public:

    explicit SqliteStatement(const SqliteConnection& connection,
    const std::string& sql);

    ~SqliteStatement();

    bool step();

    bool bindString(int index,const std::string& value) const;

    bool bindDouble(int index,const double& value) const;

    bool hasRow() const;

    /**
     * Reset binding and set statement to inital state
     */
    void reset() const;

    private:

    bool open(const SqliteConnection& connection,const std::string& sql);

    void close();

    private:

    sqlite3_stmt* pstatement;

    bool phasRow;
};

#endif