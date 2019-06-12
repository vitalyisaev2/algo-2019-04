#ifndef COMMON_SORT_HPP
#define COMMON_SORT_HPP

#include <functional>
#include <vector>

namespace algo
{
    template <typename T>
    using SortFunc = std::function<void(std::vector<T>&)>;
}

#endif