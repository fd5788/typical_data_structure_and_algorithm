#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <utility>

#include "union_find_sets.h"

using namespace std;

void test1()
{
    //redirect
    streambuf* streambuf_backup = cin.rdbuf();
    ifstream fin_stream;
    fin_stream.open("data.in");
    cin.rdbuf(fin_stream.rdbuf());

    int M;
    cin >> M;

    int arr[M][M];
    for(int i = 0 ; i < M ; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> arr[i][j];
        }
    }

    int total = M * M;
    UnionFindSets uf(total);

    int a, b;
    for(int i = 0 ; i < M ; ++i)
    {
        for(int j = 0; j < M; ++j)
        {
            a = i * M + j;
            if(!arr[i][j])
            {
                uf.reset(a, -1);
                continue;
            }
            if(j + 1 < M && arr[i][j + 1])
            {
                b = a + 1;
                uf.merge(a, b);
            }
            if(i + 1 < M && arr[i + 1][j])
            {
                b =  (i + 1) * M + j;
                uf.merge(a, b);
            }
        }
    }

    int res = 0;
    for(int i = 0; i < total; ++i)
    {
        if (uf.find(i) != -1 && uf.root(i))
        {
            res++;
        }
    }
    cout << res << endl;

    //reset redirect
    cin.rdbuf(streambuf_backup);

}

void test2()
{
    //redirect
    streambuf* streambuf_backup = cin.rdbuf();
    ifstream fin_stream;
    fin_stream.open("data2.in");
    cin.rdbuf(fin_stream.rdbuf());

    //相邻的两个表示朋友
    vector<int> vec;
    map<int, int> map;
    int a, b;
    string str;
    getline(cin, str);
    istringstream iss(str);
    while(iss >> a)
    {
        vec.push_back(a);
        if(map.find(a) == map.end())
            map.insert(pair<int, int> (a, map.size()));
    }
    UnionFindSets uf(map.size());
    for(size_t i = 0; i < vec.size(); i += 2)
    {
        uf.merge(map[vec[i]], map[vec[i + 1]]);
    }
    for(auto & i : map)
        cout << i.first << " " << i.second << " " << uf.get(i.second) << endl;
    while(cin >> a >> b)
    {
        cout << uf.connected(map[a], map[b]) << endl;
    }

    //reset redirect
    cin.rdbuf(streambuf_backup);
}

int main(void)
{
    cout << "测试1" << endl;
    test1();
    cout << "测试2" << endl;
    test2();
    return 0;
}

