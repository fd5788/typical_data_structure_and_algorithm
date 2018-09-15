#include <iostream>
#include <cstddef>

//refs->https://blog.csdn.net/smile_to_life/article/details/53383861

class twobitmap
{
public:
    twobitmap(std::size_t size): size(size / 4 + 1)
    {
        bits= new int[size]();
    }
    ~twobitmap()
    {
        delete [] bits;
    }
    //x表示一个整数，num表示bitmap中已经拥有x的个数
    //由于我们只能用2个bit来存储x的个数，所以num的个数最多为3
    void set(std::size_t x, std::size_t num)
    {
        std::size_t index = x >> 4;
        std::size_t pos = x & 0x0f;
        //将x对于为值上的个数值先清零，但是又要保证其他位置上的数不变
        bits[index] &= ~(0x03 << (2 * pos));
        //重新对x的个数赋值
        bits[index] |= ((num & 0x03) << (2 * pos));
    }

    void reset(std::size_t x)
    {
        std::size_t index = x >> 2;
        std::size_t pos = x & 0x0f;
        bits[index] &= ~(0x03 << (2 * pos));
    }

    std::size_t get(std::size_t x)
    {
        std::size_t index = x >> 2;
        std::size_t pos = x & 0x0f;
        return (bits[index] & (0x03 << (2 * pos))) >> (2 * pos);
        return 0;
    }

    void add(std::size_t x)
    {
        std::size_t num = get(x);
        if(num < 3)
            set(x, num + 1);
    }

    std::size_t length() const
    {
        return size;
    }

private:
    int* bits;
    std::size_t size;
};

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
