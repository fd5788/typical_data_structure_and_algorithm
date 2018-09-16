#include"union_find_sets.h"

UnionFindSets::UnionFindSets(int N)
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
UnionFindSets::~UnionFindSets()
{
    delete[] id;
    delete[] rank;
}
int UnionFindSets::count()
{
    return cnt;
}
bool UnionFindSets::connected(int p, int q)
{
    return find(p) == find(q);
}
int UnionFindSets::find(int p)
{
    while(p != id[p])
    {
        id[p] = id[id[p]];
        p = id[p];
    }
    return p;
}
void UnionFindSets::merge(int p, int q)
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
bool UnionFindSets::root(int p)
{
    return p == id[p];
}
void UnionFindSets::reset(int i, int val)
{
    id[i] = val;
}
