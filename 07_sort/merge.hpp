#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <iterator>

namespace algo
{

    template <typename T>
    void MergeSort(std::vector<T>& array)
    {
        std::vector<T> copy(array.size());
        std::copy(array.begin(), array.end(), copy.begin());
        SplitMerge(copy, 0, array.size(), array);
    }

    template <typename T>
    void SplitMerge(std::vector<T>& copy, size_t begin, size_t end, std::vector<T>& array)
    {
        if ((end - begin) < 2) {
            return;
        }
        size_t middle = (end - begin) / 2;
        SplitMerge(array, begin, middle, copy);
        SplitMerge(array, middle, end, copy);
        Merge(copy, begin, middle, end, array);
    }

    template <typename T>
    void Merge(std::vector<T>& copy, size_t begin, size_t end, std::vector<T>& array)
    {
        size_t p1     = begin;
        size_t middle = (end - begin) / 2;
        size_t p2     = middle;
        size_t p3     = begin;
        for (size_t p3 = begin; p3 < end; p3++) {
            if (p1 < middle && (p2 == end || copy[p1] <= copy[p2])) {
                array[p3] = copy[p1];
                p1++;
            } else {
                array[p3] = copy[p2];
                p2++;
            }
        }
    }

} // namespace algo

#endif