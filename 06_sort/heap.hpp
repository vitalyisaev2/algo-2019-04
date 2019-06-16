#ifndef HEAP_HPP
#define HEAP_HPP
#include <vector>

namespace algo
{

    template <typename T>
    void HeapDrown(std::vector<T>& array, size_t len, size_t index)
    {
        auto left    = 2 * index + 1;
        auto right   = 2 * index + 2;
        auto largest = index;
        if (left < len && array[left] > array[largest]) {
            largest = left;
        }
        if (right < len && array[right] > array[largest]) {
            largest = right;
        }
        if (largest != index) {
            std::swap(array[largest], array[index]);
            HeapDrown(array, len, largest);
        }
    }

    template <typename T>
    void HeapBuild(std::vector<T>& array)
    {
        for (int i = (array.size() - 1) / 2; i >= 0; i--) {
            HeapDrown(array, array.size(), static_cast<size_t>(i));
        }
    }

    template <typename T>
    T HeapRemoveMax(std::vector<T>& array)
    {
        if (array.size() < 1) {
            throw "Cannot remove max value from empty heap";
        }
        auto first = array[0];
        array[0]   = array.back();
        array.pop_back();
        HeapDrown(array, array.size(), 0);
        return first;
    }

    template <typename T>
    void HeapIncreaseKey(std::vector<T>& array, size_t index, T key)
    {
        if (key < array[index]) {
            throw "new key is less than elder one";
        }
        array[index] = key;
        while (index > 0 && array[(index - 1) / 2] < array[index]) {
            std::swap(array[(index - 1) / 2], array[index]);
            index = (index - 1) / 2;
        }
    }

    template <typename T>
    void HeapInsert(std::vector<T>& array, T key)
    {
        array.push_back(key);
        HeapIncreaseKey(array, array.size() - 1, key);
    }


} // namespace algo

#endif