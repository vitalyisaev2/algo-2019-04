#ifndef INSERTION_SORT_HPP
#define INSERTION_SORT_HPP

namespace algo
{

    template <typename T>
    void InsertionSort(std::vector<T>& data)
    {
        if (data.size() <= 1) {
            return;
        }
        for (size_t i = 1; i < data.size(); i++) {
            auto j = i;
            while (j > 0 && data[j - 1] > data[j]) {
                std::swap(data[j], data[j - 1]);
                j--;
            }
        }
        return;
    }

} // namespace algo

#endif