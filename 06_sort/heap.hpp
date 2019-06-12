#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>

namespace algo
{

    template <typename T>
    void HeapDrown(std::vector<T>& array, size_t index)
    {
        auto left   = 2 * index;
        auto right  = 2 * index + 1;
        auto larges = index;
        if (left < array.size() && array[left] > array[largest]) {
            largest = left;
        }
        if (right < array.size() && array[right] > array[largest]) {
            largest = right;
        }
        if (largest != index) {
            std::swap(array[largest], array[index]);
            HeapDrown(array, largest);
        }
    }

    template <typename T>
    void HeapBuild(std::vector<T>& array)
    {
        for (size_t i = static_cast<size_t>((array.size() - 1) / 2); i > 0; i--) {
            HeapDrown(array, index);
        }
    }

} // namespace algo

#endif