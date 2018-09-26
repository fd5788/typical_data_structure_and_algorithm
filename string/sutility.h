#ifndef S_UTILITY_H
#define S_UTILITY_H

#include <vector>
#include <string>
#include <cstring>
#include <sstream>

std::vector<int> split(const std::string& str, const char* delim)
{
    std::vector<int> vec;
    if(str.size() == 0) return vec;
    //char *cstr = new char[str.size() + 1];
    char *cstr = const_cast<char*>(str.c_str());
    std::strcpy(cstr, str.c_str());

    char *p = std::strtok(cstr, delim);
    int d;
    while(p)
    {
        std::sscanf(p, "%d", &d);
        vec.push_back(d);
        p = std::strtok(NULL, delim);
    }
    return vec;
}

std::vector<int> split(const std::string& str)
{
    std::vector<int> vec;
    if(str.size() == 0) return vec;

    std::istringstream iss(str);
    int d;
    char ch;
    while (iss >> d)
    {
        vec.push_back(d);
        iss >> ch;
    }

    return vec;
}

#endif
