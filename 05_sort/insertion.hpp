#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

#include <functional>
#include <vector>

template <typename T>
using sort_func = std::function<void(std::vector<T>&)>;

template <typename T>
void insertion_sort(std::vector<T>& data)
{
    if (data.size() <= 1) {
        return;
    }
    for (size_t j = 1; j < data.size(); j++) {
        auto key = data[j];
        auto i   = j - 1;
        while (i >= 0 && data[i] > key) {
            data[i + 1] = data[i];
            i--;
        }
        data[i + 1] = key;
    }
    return;
}

#endif