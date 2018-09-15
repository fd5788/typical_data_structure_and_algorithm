#include <iostream>
#include <cstddef>
#include "twobitmap.h"

int main()
{
    int a[] = {5, 8, 7, 6, 3, 1, 10, 78, 56, 34, 23, 12, 43, 54, 65, 76, 87, 98, 89, 100};
    int i;
    twobitmap s(100);
    for(i = 0; i < 20; i++)
    {
        s.set(a[i], 1);
    }
    for(i = 0; i <= 100; i++)
    {
        int m = s.get(i);
        std::cout << m << ",";
    }
    std::cout << std::endl;

    return 0;
}
