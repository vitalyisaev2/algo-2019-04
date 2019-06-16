#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include "heap.hpp"

namespace algo
{

    template <typename T>
    void HeapSort(std::vector<T>& array)
    {
        HeapBuild(array);
        for (int i = array.size() - 1; i >= 0; i--) {
            std::swap(array[0], array[static_cast<size_t>(i)]);
            HeapDrown(array, static_cast<size_t>(i), 0);
        }
    }
} // namespace algo

#endif