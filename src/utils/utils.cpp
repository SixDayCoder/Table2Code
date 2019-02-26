//
// Created by Administrator on 2019/2/25.
//

#include "utils/utils.h"
#include <dirent.h>
#include <iostream>
#include <string.h>

using std::string;

#ifndef DT_TYPE
#define DT_TYPE
enum
{
    DT_UNKNOWN = 0,
# define DT_UNKNOWN     DT_UNKNOWN
    DT_FIFO = 1,
# define DT_FIFO        DT_FIFO
    DT_CHR = 2,
# define DT_CHR         DT_CHR
    DT_DIR = 4,
# define DT_DIR         DT_DIR
    DT_BLK = 6,
# define DT_BLK         DT_BLK
    DT_REG = 8,
# define DT_REG         DT_REG
    DT_LNK = 10,
# define DT_LNK         DT_LNK
    DT_SOCK = 12,
# define DT_SOCK        DT_SOCK
    DT_WHT = 14
# define DT_WHT         DT_WHT
};
#endif

void StringUtils::SplitString(const std::string &src, std::vector<std::string> &outStringVector,
                              const std::string &delim)
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

void StringUtils::TrimString(std::string &src, char c)
{
    if(src.empty()) {
        return;
    }
    src.erase(0, src.find_first_not_of(c));
    src.erase(src.find_last_not_of(c) + 1);
}

std::string FileUtils::FileNameWithoutExtension(const char *szFilePath)
{
    //TODO: reconstruct
    if(szFilePath == nullptr) {
        return "";
    }
    std::string path(szFilePath);
    auto begpos = path.find_last_of('\\') + 1;
    auto endpos = path.find_last_of('.');
    return path.substr(begpos, endpos - begpos);
}

bool FileUtils::ListDir(const char *szDir, std::vector<std::string> &outFileVec)
{
    if(szDir == nullptr) {
        return false;
    }
    DIR *dir = opendir(szDir);
    if (dir == nullptr) {
        return false;
    }
    struct dirent* pNextFile = nullptr;
    std::string fileName;
    char szFileName[156] = {};
    while(pNextFile = readdir(dir)) {
        if(pNextFile != nullptr && !(pNextFile->d_type & DT_DIR) ) {
            strcpy(szFileName, pNextFile->d_name);
            outFileVec.push_back(szFileName);
        }
    }
    return true;
}