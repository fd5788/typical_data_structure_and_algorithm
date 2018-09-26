#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "sutility.h"

using namespace std;

void test()
{
    //redirect
    streambuf* streambuf_backup = cin.rdbuf();
    ifstream fin_stream;
    fin_stream.open("data.in");
    cin.rdbuf(fin_stream.rdbuf());

    string str;
    getline(cin, str);
    cout << "strtok" << endl;
    auto vec1 = split(str, ",");
    for(auto v : vec1)
    {
        cout << v << " ";
    }
    cout << endl;
    cout << "istringstream" << endl;
    auto vec2 = split(str);
    for(auto v : vec2)
    {
        cout << v << " ";
    }
    cout << endl;
    //reset redirect
    cin.rdbuf(streambuf_backup);
}

int main(void)
{
    test();
    return 0;
}

