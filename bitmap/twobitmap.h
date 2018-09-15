#ifndef TWO_BITMAP_H
#define TWO_BITMAP_H

#include <iostream>
#include <cstddef>

class twobitmap
{
public:
    twobitmap(std::size_t size);
    ~twobitmap();
    void set(std::size_t x, std::size_t num);
    void reset(std::size_t x);
    std::size_t get(std::size_t x) const;
    void add(std::size_t x);
    std::size_t length() const;
private:
    int* bits;
    std::size_t size;
};

#endif
