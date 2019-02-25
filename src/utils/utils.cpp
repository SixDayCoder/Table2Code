//
// Created by Administrator on 2019/2/25.
//

#include "utils/utils.h"

using std::string;

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