//
// Created by Administrator on 2019/2/25.
//

#ifndef TABLE2CODE_TABLE_MANAGER_H
#define TABLE2CODE_TABLE_MANAGER_H


#include "table/table_file.h"

#include <vector>
#include <iostream>
class ITableInstance
{
public:

    ITableInstance() = default;
    ~ITableInstance() = default;

public:

    ITableInstance(const ITableInstance&) = delete;
    ITableInstance& operator=(const ITableInstance&) = delete;

public:

    virtual void Load() = 0;
};
typedef ITableInstance *TableInstancePtr;


template<typename TableRecordType>
class TableInstance : public ITableInstance
{
public:

    TableInstance(){}
    ~TableInstance(){}

public:

    virtual void Load()
    {
        TableFile file(TableRecordType::TableFilePath());
        Load(file);
    }

    const TableRecordType* GetRecordById(int32_t nId) const
    {
        for(int32_t i = 0; i < m_Records.size(); ++i) {
            if(m_Records[i].GetId() == nId) {
                return &m_Records[i];
            }
        }
        return nullptr;
    }

    const TableRecordType* GetRecordByIndex(int32_t nIndex) const
    {
        if( nIndex < 0 || nIndex >= m_Records.size()) {
            return nullptr;
        }
        return &m_Records[nIndex];
    }

    int32_t GetRecordCount() const
    {
        return static_cast<int32_t>(m_Records.size());
    }

private:

    std::vector<TableRecordType> m_Records;

private:

    void Load(TableFile& tableFile)
    {
        m_Records.clear();
        tableFile.Load();
        TableRecordType record;
        for(int32_t nRecordIdx = 0; nRecordIdx < tableFile.RecordCount(); ++nRecordIdx) {
            record.Load(tableFile, nRecordIdx);
            m_Records.push_back(record);
        }
    }
};

//Table Impl Macros

#define TABLE_INSTANCE(Name) gTable_##Name

#define TABLE_INSTANCE_DECLARE(Name) extern TableInstance<Name> TABLE_INSTANCE(Name)

#define TABLE_INSTANCE_IMPL(Name) TableInstance<Name> TABLE_INSTANCE(Name)

//Table Operation Macros

#define TABLE_GET_BY_ID(Name) TABLE_INSTANCE(Name).GetRecordById

#define TABLE_GET_BY_INDEX(Name) TABLE_INSTANCE(Name).GetRecordByIndex

#define TABLE_GET_COUNT(Name) TABLE_INSTANCE(Name).GetRecordCount()


#endif //TABLE2CODE_TABLE_MANAGER_H
