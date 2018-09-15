#include <iostream>
#include <fstream>
#include "union_find_sets.h"

using namespace std;

void Test()
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
                uf.setParent(a, -1);
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
        if (uf.getParent(i) != -1 && uf.root(i))
            res++;
    }
    cout << res << endl;

    //reset redirect
    cin.rdbuf(streambuf_backup);

}

int main(void)
{
    Test();
    return 0;
}

