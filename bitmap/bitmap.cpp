#include <iostream>
#include <cstddef>
#include "bitmap.h"

bitmap::bitmap(std::size_t size) : size((size >> 3) + 1)
{
    bits = new char[size]();
}

bitmap::~bitmap()
{
    delete[] bits;
}

void bitmap::set(std::size_t x)
{
    std::size_t index = x >> 3;
    std::size_t pos = x & 0x07;
	bits[index] |= 1 << pos;
}

void bitmap::reset(std::size_t x)
{
    std::size_t index = x >> 3;
    std::size_t pos = x & 0x07;
	bits[index] &= ~(1 << pos);
}

bool bitmap::get(std::size_t x) const
{
    std::size_t index = x >> 3;
    std::size_t pos = x & 0x07;
	return (bits[index] & (1 << pos));
}

std::size_t bitmap::length() const
{
    return size;
}
