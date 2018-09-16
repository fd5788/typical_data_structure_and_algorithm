#include <iostream>
#include <fstream>

class UnionFindSets
{
public:
    UnionFindSets(int N)
    {
        cnt = N;
        id = new int[N];
        rank = new int[N];
        for (int i = 0; i < N; i++)
        {
            id[i] = i;
            rank[i] = 1;
        }
    }
    ~UnionFindSets()
    {
        delete[] id;
        delete[] rank;
    }
    int count() const
    {
        return cnt;
    }
    bool connected(int p, int q)
    {
        return find(p) == find(q);
    }
    int find(int p)
    {
        ////递归
        //if(p != id[p])
        //{
            //id[p] = find(id[p]);
        //}
        //return id[p];
        //非递归
        while(p != id[p])
        {
            id[p] = id[id[p]];
            p = id[p];
        }
        return p;
    }
    void merge(int p, int q)
    {
        int i = find(p);
        int j = find(q);
        if(i == j) return;
        if(rank[i] < rank[j])
        {
            id[i] = j;
            rank[j] += rank[i];
        }
        else
        {
            id[j] = i;
            rank[i] += rank[j];
        }
        cnt--;
    }
    bool root(int p) const
    {
        return p == id[p];
    }
    void reset(int p, int val)
    {
        id[p] = val;
    }
    int get(int p)
    {
        return id[p];
    }
private:
    int cnt;
    int* id;
    int* rank;
};

/**
    //redict
    streambuf *backup = cin.rdbuf();
    ifstream fin;
    fin.open("data.in");
    cin.rdbuf(fin.rdbuf());

    //reset redict
    cin.rdbuf(backup);
*/
