#include <string>
#include <iostream>
#include <stdio.h>

#include "table/table_test.h"
#include "table/table_manager.h"

using namespace std;

void TestTableFile(const char* szTableName)
{
    TableFile file(szTableName);

    int32_t nCnt = TABLE_GET_BY_COUNT(Table_Test);
    const Table_Test* recordx = TABLE_GET_BY_ID(Table_Test)(2);
    const Table_Test* recordy = TABLE_GET_BY_INDEX(Table_Test)(0);

    cout << nCnt << endl;
    if(recordx != nullptr) {
        cout << recordx->GetId() << " " << recordx->GetInt32Val() << " " << recordx->GetInt64Val() << endl;
    }
    if(recordy != nullptr) {
        cout << recordy->GetId() << " " << recordy->GetInt32Val() << " " << recordy->GetInt64Val() << endl;
    }
}

int main()
{
    const char* dir = "D:\\Table2Code\\tables\\Test.txt";
    TestTableFile(dir);
    return 0;
}