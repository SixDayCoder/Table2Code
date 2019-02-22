//
// Created by Administrator on 2019/2/20.
//

#include "table/table_file.h"

#include <assert.h>
#include <fstream>
#include <iostream>
#include <vector>


using std::string;
using std::vector;

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

//--------------------------------------------TableRecordString Utlis--------------------------------------------//

static void SplitString(const string& src, vector<string>& outStringVector, const string& delim)
{
    string::size_type begIndex = 0;
    string::size_type endIndex = src.find(delim);

    while(string::npos != endIndex) {
        outStringVector.push_back(src.substr(begIndex, endIndex - begIndex));
        begIndex = endIndex + delim.size();
        endIndex = src.find(delim, begIndex);
    }
    if(begIndex != src.length()) {
        outStringVector.push_back(src.substr(begIndex, src.length() - begIndex));
    }
}

static void TrimString(string& src, char c)
{
    if(src.empty()) {
        return;
    }
    src.erase(0, src.find_first_not_of(c));
    src.erase(src.find_last_not_of(c) + 1);
}

TableFile::TableFile(const char *szFilePath)
{
    assert(szFilePath != nullptr);
    m_szFilePath = szFilePath;
    m_szFileName = m_szFilePath.substr(m_szFilePath.find_last_of('\\') + 1);
}

void TableFile::Load()
{
    std::ifstream input(m_szFilePath, std::ios::in | std::ios::binary);
    char buffer[1024];
    int32_t nLineIndex = 0;
    while(!input.eof() && !input.bad()) {
        input.getline(buffer, 1024);
        ParseRecord(buffer, nLineIndex++);
    }
    input.close();
}

void TableFile::Read(int32_t &nValInt32, int32_t nRecordIndex, int32_t nIndexInRecord) const
{
    assert(m_RecordType[nIndexInRecord] == TableCellType::TABLE_CELL_TYPE_INT32);
    assert(nRecordIndex >= 0 && nRecordIndex < m_Records.size());
    const TableRecordString& records = m_Records[nRecordIndex];
    assert(nIndexInRecord >= 0 && nIndexInRecord < records.size());
    const std::string& cell = records[nIndexInRecord];
    nValInt32 = std::stoi(cell);
}


void TableFile::Read(int64_t &nValInt64, int32_t nRecordIndex, int32_t nIndexInRecord) const
{
    assert(m_RecordType[nIndexInRecord] == TableCellType::TABLE_CELL_TYPE_INT64);
    assert(nRecordIndex >= 0 && nRecordIndex < m_Records.size());
    const TableRecordString& records = m_Records[nRecordIndex];
    assert(nIndexInRecord >= 0 && nIndexInRecord < records.size());
    const std::string& cell = records[nIndexInRecord];
    nValInt64 = static_cast<int64_t>(std::stoll(cell));
}

void TableFile::Read(std::string &szValStr, int32_t nRecordIndex, int32_t nIndexInRecord) const
{
    assert(m_RecordType[nIndexInRecord] == TableCellType::TABLE_CELL_TYPE_STRING);
    assert(nRecordIndex >= 0 && nRecordIndex < m_Records.size());
    const TableRecordString& records = m_Records[nRecordIndex];
    assert(nIndexInRecord >= 0 && nIndexInRecord < records.size());
    const std::string& cell = records[nIndexInRecord];
    szValStr = cell;
}

void TableFile::Read(float &fValReal, int32_t nRecordIndex, int32_t nIndexInRecord) const
{
    assert(m_RecordType[nIndexInRecord] == TableCellType::TABLE_CELL_TYPE_FLOAT);
    assert(nRecordIndex >= 0 && nRecordIndex < m_Records.size());
    const TableRecordString& records = m_Records[nRecordIndex];
    assert(nIndexInRecord >= 0 && nIndexInRecord < records.size());
    const std::string& cell = records[nIndexInRecord];
    fValReal = std::stof(cell);
}

void TableFile::ParseRecord(const char *line, int32_t nLineIndex)
{
    if(nLineIndex == TABLE_LINE_INDEX_NAME || nLineIndex == TABLE_LINE_INDEX_DESC) {
        return;
    }

    string buffer(line);
    TrimString(buffer, '\r');
    TrimString(buffer, '\n');
    TrimString(buffer, ' ');

    if(buffer.empty()) {
        return;
    }

    TableRecordString record;
    SplitString(buffer, record, "\t");

    if(nLineIndex == TABLE_LINE_INDEX_TYPE) {
        for(auto it = record.begin(); it != record.end(); it++) {
            int32_t nTypeNumber = TableCellType::GetTypeNumber(it->c_str());
            assert(nTypeNumber != -1);
            m_RecordType.push_back(nTypeNumber);
        }
        return;
    }
    m_Records.push_back(record);
}
