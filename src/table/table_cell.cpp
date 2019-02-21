#include "table/table_cell.h"

bool TableCellType::IsInit = false;
std::map<std::string, int32_t> TableCellType::TypeMap;

void TableCellType::InitTypeMap()
{
    TypeMap[TableCellType::INT32] = TableCellType::TABLE_CELL_TYPE_INT32;
    TypeMap[TableCellType::INT64] = TableCellType::TABLE_CELL_TYPE_INT64;
    TypeMap[TableCellType::STRING] = TableCellType::TABLE_CELL_TYPE_STRING;
    TypeMap[TableCellType::FLOAT] = TableCellType::TABLE_CELL_TYPE_FLOAT;
    IsInit = true;
}

int32_t TableCellType::GetTypeNumber(const char *szTypeString)
{
    if(!IsInit) {
        InitTypeMap();
    }
    auto it = TypeMap.find(szTypeString);
    if(it != TypeMap.end()) {
        return it->second;
    }
    return -1;
}