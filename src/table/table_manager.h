#ifndef TABLE2CODE_TABLE_MANAGER_H_
#define TABLE2CODE_TABLE_MANAGER_H_

#include "table/table_instance.h"
#include <map>
#include <string>

class TableManager
{
public:

    TableManager(){}
    ~TableManager(){}

public:

    static void Load();

private:

    static std::map<std::string, TableInstancePtr> gTableMap;
};

#endif