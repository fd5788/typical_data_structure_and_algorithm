#include <iostream>
#include <cstddef>
#include "twobitmap.h"

    twobitmap::twobitmap(std::size_t size): size(size / 4 + 1)
    {
        bits= new int[size]();
    }

    twobitmap::~twobitmap()
    {
        delete [] bits;
    }
    //x表示一个整数，num表示bitmap中已经拥有x的个数
    //由于我们只能用2个bit来存储x的个数，所以num的个数最多为3
    void twobitmap::set(std::size_t x, std::size_t num)
    {
        std::size_t index = x >> 4;
        std::size_t pos = x & 0x0f;
        //将x对于为值上的个数值先清零，但是又要保证其他位置上的数不变
        bits[index] &= ~(0x03 << (2 * pos));
        //重新对x的个数赋值
        bits[index] |= ((num & 0x03) << (2 * pos));
    }

    void twobitmap::reset(std::size_t x)
    {
        std::size_t index = x >> 2;
        std::size_t pos = x & 0x0f;
        bits[index] &= ~(0x03 << (2 * pos));
    }

    std::size_t twobitmap::get(std::size_t x) const
    {
        std::size_t index = x >> 2;
        std::size_t pos = x & 0x0f;
        return (bits[index] & (0x03 << (2 * pos))) >> (2 * pos);
        return 0;
    }

    void twobitmap::add(std::size_t x)
    {
        std::size_t num = get(x);
        if(num < 3)
            set(x, num + 1);
    }

    std::size_t twobitmap::length() const
    {
        return size;
    }
