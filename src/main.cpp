#include <string>
#include <iostream>
#include <stdio.h>

#include "utils/utils.h"
#include "table/table_test.h"
#include "table/table_item.h"
#include "table/table_manager.h"

using namespace std;

void LoadTables()
{
    TableManager::Load();

    int32_t nCnt = 0;
    cout << "Table_Test Begin" << endl;
    nCnt = TABLE_GET_BY_COUNT(Table_Test);
    for(int32_t i = 0; i < nCnt; ++i) {
        const Table_Test* record = TABLE_GET_BY_INDEX(Table_Test)(i);
        if(record != nullptr) {
            cout << record->GetId() << " " << record->GetInt32Val() << " " << record->GetInt64Val() << " " << record->GetStringVal() << endl;
        }
    }
    cout << "Table_Test End" << endl;

    cout << "Table_Item Begin" << endl;
    nCnt = TABLE_GET_BY_COUNT(Table_Item);
    for(int32_t i = 0; i < nCnt; ++i) {
        const Table_Item* record = TABLE_GET_BY_INDEX(Table_Item)(i);
        if(record != nullptr) {
            cout << record->GetId() << " " << record->GetPrice() << " " << record->GetStackCount() << " " << record->GetDataId() << endl;
        }
    }
    cout << "Table_Item End" << endl;
}

int main()
{
    LoadTables();
    return 0;
}