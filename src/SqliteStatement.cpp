#include "SqliteStatement.h"
#include "SqliteConnection.h"

SqliteStatement::SqliteStatement(const SqliteConnection& connection,
const std::string& sql):
pstatement{nullptr}
{   
    open(connection,sql);
}

SqliteStatement::~SqliteStatement()
{
    close();
}

bool SqliteStatement::step()
{
    if(!pstatement){
        return false;
    }

    int result = sqlite3_step(pstatement);
    
    if(result==SQLITE_ROW){

        phasRow = true;

        return true;

    }else if(result==SQLITE_DONE){

        phasRow = false;

        return true;
    }

    

    return false;
}

bool SqliteStatement::bindString(int index,const std::string& value) const
{
    if(!pstatement){
        return false;
    }

    return sqlite3_bind_text(pstatement,index,value.c_str(),
    static_cast<int>(value.size()),SQLITE_TRANSIENT)==SQLITE_OK;
}

bool SqliteStatement::bindDouble(int index,const double& value) const
{   
    if(!pstatement){
        return false;
    }

    return sqlite3_bind_double(pstatement,index,value)==SQLITE_OK;
}

bool SqliteStatement::hasRow() const
{
    return phasRow;
}

void SqliteStatement::reset() const
{
    if(pstatement){
        sqlite3_reset(pstatement);
        sqlite3_clear_bindings(pstatement);
    }
}

bool SqliteStatement::open(const SqliteConnection& connection,const std::string& sql)
{
    sqlite3* openedConnection = connection.getConnection();

    if(!openedConnection){
        return false;
    }

   
    return sqlite3_prepare_v2(openedConnection,
    sql.c_str(),
    static_cast<int>(sql.size()),
    &pstatement,
    nullptr)==SQLITE_OK;
}

void SqliteStatement::close()
{
    if(pstatement){

        sqlite3_finalize(pstatement);

        pstatement = nullptr;
    }
}