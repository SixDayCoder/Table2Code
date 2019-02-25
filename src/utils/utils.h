//
// Created by Administrator on 2019/2/25.
//

#ifndef TABLE2CODE_UTILS_H
#define TABLE2CODE_UTILS_H

#include <string>
#include <vector>
#include <dirent.h>

class StringUtils
{
public:

    static void SplitString(const std::string& src, std::vector<std::string>& outStringVector, const std::string& delim);

    static void TrimString(std::string& src, char c);

};

class FileUtils
{

};

#endif //TABLE2CODE_UTILS_H
