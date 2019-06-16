#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <vector>

namespace algo
{

    template <typename T>
    void quickSortStep(std::vector<T>& array, int begin, int end)
    {

        // схема Ловато
        auto partition = [&](int low, int high) -> int {
            T   pivot = array[size_t(high)];
            int i     = low - 1; // ??
            for (int j = low; j <= high - 1; j++) {
                if (array[size_t(j)] <= pivot) {
                    i++;
                    std::swap(array[size_t(i)], array[size_t(j)]);
                }
            }
            std::swap(array[size_t(i + 1)], array[size_t(high)]);
            return i + 1;
        };

        // рекурсивная сортировка
        if (begin < end) {
            auto pivot = partition(begin, end);
            quickSortStep(array, begin, pivot - 1);
            quickSortStep(array, pivot + 1, end);
        }
    }

    template <typename T>
    void QuickSort(std::vector<T>& array)
    {
        if (array.size() < 1) {
            return;
        }
        quickSortStep(array, 0, array.size() - 1);
    }

} // namespace algo

#endif