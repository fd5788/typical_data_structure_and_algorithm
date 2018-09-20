#include"union_find_sets.h"

//N为最大元数+1, 对于稀疏序列，先用map映射一下
UnionFindSets::UnionFindSets(int N)
{
    cnt = N;
    id = new int[N];
    rank = new int[N];
    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        rank[i] = 0;
    }
}
UnionFindSets::~UnionFindSets()
{
    delete[] id;
    delete[] rank;
}
int UnionFindSets::count() const
{
    return cnt;
}
bool UnionFindSets::connected(int p, int q)
{
    return find(p) == find(q);
}
int UnionFindSets::find(int p)
{
    ////递归
    //if(p != id[p])
    //{
        //id[p] = find(id[p]);
    //}
    //return id[p];
    //非递归
    //fin d root
    int r = p;
    while(r != id[r])
        r = id[r];
    while(p != id[p])
    {
        int t = id[p];
        id[p] = r;
        p = t;
    }
    return p;
}
void UnionFindSets::merge(int p, int q)
{
    int i = find(p);
    int j = find(q);
    if(i == j) return;
    if(rank[i] > rank[j])
    {
        id[j] = i;
    }
    else
    {
        id[i] = j;
        if(rank[i] == rank[j])
            rank[j]++;
    }
    cnt--;
}
bool UnionFindSets::root(int p) const
{
    return p == id[p];
}
void UnionFindSets::reset(int p, int val)
{
    id[p] = val;
}
int UnionFindSets::get(int p) const
{
    return id[p];
}
