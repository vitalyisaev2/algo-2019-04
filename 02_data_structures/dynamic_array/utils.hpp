#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>
#include <sstream>

template <typename T>
void copyPointerArray(T* from, T* to, size_t num)
{
    while (num--) {
        *to++ = *from++;
    }
}

template <typename T>
void shiftPointerArrayRight(T* from, size_t length)
{
    from += length;
    while (length--) {
        *from = *(from - 1);
        from--;
    }
}

template <typename T>
void shiftPointerArrayLeft(T* from, size_t length)
{
    while (length--) {
        *from = *(from + 1);
        from++;
    }
}

enum ResizeMode {
    Grow,
    Shrink,
};

std::string invalidIndexNumber(size_t size, size_t index);

std::string invalidIndexNumber(size_t size, size_t index)
{
    std::stringstream ss;
    ss << "invalid index value (size: " << size << ", index: " << index << ")";
    return ss.str();
}

#endif