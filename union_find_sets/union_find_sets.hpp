#ifndef UNION_FIND_SETS_HPP
#define UNION_FIND_SETS_HPP

class UnionFindSets
{
private:
    int cnt;
    int* id;
    int* rank;
public:
    UnionFindSets(int N);
    ~UnionFindSets();
    int count();
    bool connected(int p, int q);
    int find(int p);
    void merge(int p, int q);
    bool root(int p);
    int getParent(int i);
    void setParent(int i, int val);
};

#endif
