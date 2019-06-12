#ifndef COMMON_SORT_HPP
#define COMMON_SORT_HPP

#include <functional>
#include <vector>

template <typename T>
using sort_func = std::function<void(std::vector<T>&)>;

#endif