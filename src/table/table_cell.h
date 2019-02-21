//
// Created by Administrator on 2019/2/20.
//

#ifndef TABLE2CODE_TABLE_CELL_H
#define TABLE2CODE_TABLE_CELL_H


#include <assert.h>
#include <stdint.h>
#include <string>
#include <map>

class TableCellType
{
public:

    enum
    {
        TABLE_CELL_TYPE_INT32 = 0,//int32
        TABLE_CELL_TYPE_INT64 = 1,//int64
        TABLE_CELL_TYPE_STRING = 2,//string
        TABLE_CELL_TYPE_FLOAT = 3,//float
    };

public:

    static int32_t GetTypeNumber(const char* szTypeString);

public:

    static constexpr const char* INT32  = "INT32";
    static constexpr const char* INT64  = "INT64";
    static constexpr const char* STRING = "STRING";
    static constexpr const char* FLOAT   = "FLOAT";

private:

    static void InitTypeMap();

    static bool IsInit;
    static std::map<std::string, int32_t> TypeMap;
};


template<typename ElementT, int Type>
class TableCell
{
public:

    explicit TableCell(const ElementT& elem)
    {
        m_Element = elem;
    }

    ~TableCell() = default;

public:

    int GetType() const { return Type; }

    const ElementT& GetElem() const { return m_Element; }

private:

    ElementT m_Element;
};

template<>
class TableCell<std::string, TableCellType::TABLE_CELL_TYPE_STRING>
{
public:

    explicit TableCell(const std::string& elem)
    {
        m_Element = elem;
    }

    ~TableCell() = default;

public:

    int GetType() const { return TableCellType::TABLE_CELL_TYPE_STRING; }

    const char* GetElem() const { return m_Element.c_str(); }

private:

    std::string m_Element;
};


using TableCellInt32 = TableCell<int32_t, TableCellType::TABLE_CELL_TYPE_INT32>;
using TableCellInt64 = TableCell<int64_t, TableCellType::TABLE_CELL_TYPE_INT64>;
using TableCellString = TableCell<std::string, TableCellType::TABLE_CELL_TYPE_STRING>;
using TableCellReal = TableCell<float, TableCellType::TABLE_CELL_TYPE_FLOAT>;

#endif //TABLE2CODE_TABLE_CELL_H
