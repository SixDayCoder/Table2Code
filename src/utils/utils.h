//
// Created by Administrator on 2019/2/25.
//

#ifndef TABLE2CODE_UTILS_H
#define TABLE2CODE_UTILS_H

#include <string>
#include <vector>

class StringUtils
{
public:

    static void SplitString(const std::string& src, std::vector<std::string>& outStringVector, const std::string& delim);

    static void TrimString(std::string& src, char c);

};

class FileUtils
{
public:
    static std::string FileNameWithoutExtension(const char* szFilePath);

    static bool ListDir(const char* szDir, std::vector<std::string>& outFileVec);
};

#endif //TABLE2CODE_UTILS_H
