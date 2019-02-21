//
// Created by Administrator on 2019/2/20.
//

#ifndef TABLE2CODE_TABLE_FILE_H
#define TABLE2CODE_TABLE_FILE_H

#include <stdint.h>
#include <string>
#include <vector>
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



using TableRecordString = std::vector<std::string>;
class TableFile
{
public:

    enum
    {
        TABLE_LINE_INDEX_NAME = 0,
        TABLE_LINE_INDEX_TYPE = 1,
        TABLE_LINE_INDEX_DESC = 2,
    };

public:

    TableFile(const char* szFilePath);

    ~TableFile() {}

public:

    void Load();

    int32_t RecordCount() const { return static_cast<int32_t>(m_Records.size()); }

public:

    void Read(int32_t& nValInt32, int32_t nRecordIndex, int32_t nIndexInRecord) const;

    void Read(int64_t& nValInt64, int32_t nRecordIndex, int32_t nIndexInRecord) const;

    void Read(std::string& szValStr, int32_t nRecordIndex, int32_t nIndexInRecord) const;

    void Read(float& fValReal, int32_t nRecordIndex, int32_t nIndexInRecord) const;

private:

    void ParseRecord(const char* line, int32_t nLineIndex);

private:

    std::string m_szFilePath;
    std::string m_szFileName;

    std::vector<int32_t> m_RecordType;
    std::vector<TableRecordString> m_Records;
};


#endif //TABLE2CODE_TABLE_FILE_H
