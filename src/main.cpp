#include <string>
#include <iostream>
#include <stdio.h>

#include "utils/utils.h"
#include "table/table_test.h"

using namespace std;

void LoadTables()
{
    const char* szDir = "D:\\Table2Code\\tables";
    std::vector<std::string> files;
    if(FileUtils::ListDir(szDir, files)) {
        for(auto name : files) {
            cout << name << endl;
        }
    }

}

void TestTableFile(const char* szTableFilePath)
{
    TableFile file(szTableFilePath);
    std::string tableName = FileUtils::FileNameWithoutExtension(szTableFilePath);

    TABLE_INSTANCE(Table_Test).Load(file);

    int32_t nCnt = TABLE_GET_BY_COUNT(Table_Test);
    const Table_Test* recordx = TABLE_GET_BY_ID(Table_Test)(2);
    const Table_Test* recordy = TABLE_GET_BY_INDEX(Table_Test)(0);

    cout << tableName << " " << nCnt << endl;
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
    LoadTables();
    TestTableFile(dir);
    return 0;
}