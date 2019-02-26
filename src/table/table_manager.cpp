//
// Created by Administrator on 2019/2/26.
//


//auto generate
#include "table/table_manager.h"
#include "table/table_test.h"
#include "table/table_item.h"

std::map<std::string, TableInstancePtr> TableManager::gTableMap;

void TableManager::Load()
{
    TABLE_INSTANCE(Table_Test).Load();
    gTableMap.insert(std::make_pair(Table_Test::TableFilePath(), &TABLE_INSTANCE(Table_Test)));

    TABLE_INSTANCE(Table_Item).Load();
    gTableMap.insert(std::make_pair(Table_Test::TableFilePath(), &TABLE_INSTANCE(Table_Item)));
}
