#ifndef SQLITE_TRANSACTION_H

#define SQLITE_TRANSACTION_H

#include "SqliteConnection.h"

class SqliteTransaction final
{
    public:

    /**
     * Begin the transaction
     */
    explicit SqliteTransaction(const SqliteConnection& connection);

    ~SqliteTransaction();

    //transaction must be non-copyable

    SqliteTransaction(const SqliteTransaction&) = delete;

    SqliteTransaction& operator=(const SqliteTransaction&) = delete;

    bool commit();

    private:

    SqliteConnection pconnection;

    bool pisCommited; 
};

#endif