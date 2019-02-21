#include <string>
#include <iostream>
#include <stdio.h>

#include "table/table_test.h"

using namespace std;

void TestTableRecord()
{
    TableCellInt32 cellInt32(500);
    printf("Int32 : %d Type : %d\n", cellInt32.GetElem(), cellInt32.GetType());

    TableCellInt64 cellInt64(3123123123123123123);
    printf("Int64 : %ld Type : %d\n", cellInt64.GetElem(), cellInt64.GetType());

    TableCellString cellString("hello world");
    printf("string : %s Type : %d\n", cellString.GetElem(), cellString.GetType());

    TableCellReal cellReal(31.23231f);
    printf("Float : %f Type : %d\n", cellReal.GetElem(), cellReal.GetType());
}

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