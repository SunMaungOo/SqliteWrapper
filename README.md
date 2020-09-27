# SqliteWrapper

Simple RAII C++ Sqlite wrapper.

**Important : This library only support inserting row and cannot read from database**


**Creating database**

```cpp

 std::string databaseLocation = "test.db3";

 SqliteConnection connection{databaseLocation};

 connection.exec("CREATE TABLE MyTable(Column1 text,Column2 real);")


```

**Inserting rows**

```cpp

  std::string databaseLocation = "test.db3";

  SqliteConnection connection{databaseLocation};

  SqliteTransaction transaction{connection};

  SqliteStatement statement{connection,"INSERT INTO MyTable(Column1,Column2) VALUES(?,?);"};

  //insert multiple row

  for(auto i=0;i<data.size();i++){

      //bind the parameter

      statement.bindString(1,data[i].getStr());
      statement.bindDouble(2,data[i].getDouble());

      statement.reset();
  }
  
  //commit the transaction

  transaction.commit();

```