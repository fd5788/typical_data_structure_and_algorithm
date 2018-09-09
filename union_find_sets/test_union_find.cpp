#include <iostream>
#include <fstream>
#include "union_find_sets.hpp"

using namespace std;

void Test()
{
    //redict
    streambuf *backup = cin.rdbuf();
    ifstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

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

    //reset redict
    cin.rdbuf(backup);

}

int main(void)
{
    Test();
    return 0;
}

