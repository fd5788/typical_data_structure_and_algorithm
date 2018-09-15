#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>
#include <cstddef>

class bitmap
{
public:
	bitmap(std::size_t size);
    ~bitmap();

	void set(std::size_t num);
	void reset(std::size_t num);
	bool get(std::size_t num) const;
    std::size_t length() const;

private:
	char* bits;
    std::size_t size;
};

#endif
