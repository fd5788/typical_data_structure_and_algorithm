#include <iostream>
#include <cstddef>

class bitmap
{
public:
	bitmap(std::size_t size) : size((size >> 3) + 1)
	{
		bits = new char[size]();
	}
    ~bitmap()
    {
        delete[] bits;
    }

	void set(std::size_t num)
	{
        std::size_t index = num >> 3;
        std::size_t pos = num & 0x07;
		bits[index] |= 1 << pos;
	}

	void reset(std::size_t num)
	{
        std::size_t index = num >> 3;
        std::size_t pos = num & 0x07;
		bits[index] &= ~(1 << pos);
	}

	bool get(std::size_t num) const
	{
        std::size_t index = num >> 3;
        std::size_t pos = num & 0x07;
        return (bits[index] & (1 << pos));
	}

    std::size_t length() const
    {
        return size;
    }

private:
	char* bits;
    std::size_t size;
};
