#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>

std::vector<int> split_k(const std::string& str, const char* delim)
{
    std::vector<int> vec;
    if(str.size() == 0) return vec;
    char *c_str = (char *) str.c_str();
    std::strcpy(c_str, str.c_str());

    char *p = std::strtok(c_str, delim);
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
