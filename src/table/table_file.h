//
// Created by Administrator on 2019/2/20.
//

#ifndef TABLE2CODE_TABLE_FILE_H
#define TABLE2CODE_TABLE_FILE_H

#include <stdint.h>
#include <string>

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

public:

    void Read(int32_t& nValInt32, int32_t nRecordIndex, int32_t nIndexInRecord);

    void Read(int64_t& nValInt64, int32_t nRecordIndex, int32_t nIndexInRecord);

    void Read(std::string& szValStr, int32_t nRecordIndex, int32_t nIndexInRecord);

    void Read(float& fValReal, int32_t nRecordIndex, int32_t nIndexInRecord);

private:

    void ParseRecord(const char* line, int32_t nLineIndex);

private:

    std::string m_szFilePath;
    std::string m_szFileName;


};


#endif //TABLE2CODE_TABLE_FILE_H
