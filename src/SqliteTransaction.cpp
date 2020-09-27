#include "SqliteTransaction.h"

SqliteTransaction::SqliteTransaction(const SqliteConnection& connection)
:pconnection{connection},
pisCommited{false}
{
    pconnection.exec("BEGIN");
}

SqliteTransaction::~SqliteTransaction()
{
    //if the transaction is not commited, we rollback

    if(!pisCommited){

        pconnection.exec("ROLLBACK");     
    }
}

bool SqliteTransaction::commit()
{
    //already commited

    if(pisCommited){
        return false;
    }

    return pconnection.exec("COMMIT");
}