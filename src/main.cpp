#include <string>
#include <iostream>
#include <stdio.h>

#include "table/table_test.h"

using namespace std;

void TestTableFile(const char* szTableName)
{
    TableFile file(szTableName);
    file.Load();

    Table_Test test;
    for(int32_t nRecordIdx = 0; nRecordIdx < file.RecordCount(); ++nRecordIdx) {
        test.Load(file, nRecordIdx);
        cout << test.GetId() << " " << test.GetInt32Val() << " " << test.GetInt64Val() << " " << test.GetFloatVal() << " " << test.GetStringVal() << endl;
    }
}

int main()
{
    const char* dir = "D:\\Table2Code\\tables\\TestTable.txt";
    TestTableFile(dir);
    return 0;
}