#include <string>
#include <iostream>
#include <stdio.h>

#include "utils/utils.h"
#include "table/table_test.h"
#include "table/table_item.h"
#include "table/table_array.h"
#include "table/table_complex.h"
#include "table/table_manager.h"

using namespace std;

void LoadTables()
{
    TableManager::Load();
    int32_t nCnt = 0;
    cout << "Table_Test Begin" << endl;
    nCnt = TABLE_GET_BY_COUNT(Table_Test);
    cout << "nCnt " << nCnt << endl;
    for(int32_t i = 0; i < nCnt; ++i) {
        const Table_Test* record = TABLE_GET_BY_INDEX(Table_Test)(i);
        if(record != nullptr) {
            cout << record->GetId() << " " << record->GetInt32Val() << " " << record->GetInt64Val() << " " << record->GetStringVal() << endl;
        }
    }
    cout << "Table_Test End" << endl;

    cout << "Table_Item Begin" << endl;
    nCnt = TABLE_GET_BY_COUNT(Table_Item);
    cout << "nCnt " << nCnt << endl;
    for(int32_t i = 0; i < nCnt; ++i) {
        const Table_Item* record = TABLE_GET_BY_INDEX(Table_Item)(i);
        if(record != nullptr) {
            cout << record->GetId() << " " << record->GetPrice() << " " << record->GetStackCount() << " " << record->GetDataId() << endl;
        }
    }
    cout << "Table_Item End" << endl;

    cout << "Table_Array Begin" << endl;
    nCnt = TABLE_GET_BY_COUNT(Table_Array);
    cout << "nCnt " << nCnt << endl;
    for(int32_t i = 0; i < nCnt; ++i) {
        const Table_Array* record = TABLE_GET_BY_INDEX(Table_Array)(i);
        if(record != nullptr) {
            cout << " id : " << record->GetId() << " " << " skillid : " << record->GetSkillId() << endl;
            int nTypeCount = record->GetSkillDamgeTypeCount();
            cout << "Type ";
            for(int32_t j = 0; j < nTypeCount; ++j) {
                cout << record->GetSkillDamgeTypeByIndex(j) << " ";
            }
            cout << endl;

            cout << "Val ";
            int nValCount = record->GetSkillDamageValCount();
            for(int32_t j = 0; j < nValCount; ++j) {
                cout << record->GetSkillDamageValByIndex(j) << " ";
            }
            cout << endl;
        }
    }
    cout << "Table_Array End" << endl;

    cout << "Table_Complex Begin" << endl;
    nCnt = TABLE_GET_BY_COUNT(Table_Complex);
    cout << "nCnt " << nCnt << endl;
    for(int32_t i = 0; i < nCnt; ++i) {
        const Table_Complex* record = TABLE_GET_BY_INDEX(Table_Complex)(i);
        if(record != nullptr) {
            cout << record->GetRate() << " " << record->GetTime() << endl;
            int32_t nExIdCnt = record->GetSkillExIdCount();
            cout << "ExId ";
            for(int32_t j = 0; j < nExIdCnt; ++j) {
                cout << record->GetSkillExIdByIndex(j) << " ";
            }
            cout << endl;
        }
    }
    cout << "Table_Complex End" << endl;
}

int main()
{
    LoadTables();
    return 0;
}