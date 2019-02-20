//
// Created by Administrator on 2019/2/20.
//

#include "table/table_file.h"

#include <assert.h>
#include <fstream>
#include <iostream>
#include <vector>

using  namespace std;

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
}

void TableFile::Read(int64_t &nValInt64, int32_t nRecordIndex, int32_t nIndexInRecord)
{

}

void TableFile::Read(std::string &szValStr, int32_t nRecordIndex, int32_t nIndexInRecord)
{

}

void TableFile::Read(float &fValReal, int32_t nRecordIndex, int32_t nIndexInRecord)
{

}

void TableFile::ParseRecord(const char *line, int32_t nLineIndex)
{
    string buffer(line);
    TrimString(buffer, '\r');
    TrimString(buffer, '\n');
    TrimString(buffer, ' ');

    vector<string> elements;
    if(nLineIndex == TABLE_LINE_INDEX_NAME) {
        SplitString(buffer, elements, "\t");
        for(auto it = elements.begin(); it != elements.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
        return;
    }

    if(nLineIndex == TABLE_LINE_INDEX_TYPE) {
        SplitString(buffer, elements, "\t");
        for(auto it = elements.begin(); it != elements.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
        return;
    }

    if(nLineIndex == TABLE_LINE_INDEX_DESC) {
        SplitString(buffer, elements, "\t");
        for(auto it = elements.begin(); it != elements.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
        return;
    }

}
