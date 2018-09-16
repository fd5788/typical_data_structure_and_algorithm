#ifndef UNION_FIND_SETS_H
#define UNION_FIND_SETS_H

class UnionFindSets
{
public:
    UnionFindSets(int N);
    ~UnionFindSets();
    int count();
    bool connected(int p, int q);
    int find(int p);
    void merge(int p, int q);
    bool root(int p);
    void reset(int i, int val);
private:
    int cnt;
    int* id;
    int* rank;
};

#endif
