#ifndef RADIX_SORT_HPP
#define RADIX_SORT_HPP

#include <algorithm>
#include <array>
#include <vector>

namespace algo
{
    template <typename T>
    void RadixSort(std::vector<T>& array)
    {
        if (array.size() < 2) {
            return;
        }

        std::vector<T> output;
        output.resize(array.size());

        // используется модификация сортировки подсчётом
        auto countSort = [&](int exp) {

            // подсчитываем количество цифр
            std::array<size_t, 10> count;
            count.fill(0);
            for (size_t i = 0; i < array.size(); i++) {
                auto ix = static_cast<size_t>((array[i] / exp) % 10);
                count[ix]++;
            }

            // подсчитываем накопленные суммы
            for (size_t i = 1; i < 10; i++) {
                count[i] += count[i - 1];
            }

            // формируем вспомогательный массив, отсортированный по разряду
            for (int i = array.size() - 1; i >= 0; i--) {
                auto p                = static_cast<size_t>(i);
                auto ix               = static_cast<size_t>(array[p] / exp) % 10;
                output[count[ix] - 1] = array[p];
                count[ix]--;
            }

            // копируем данные из вспомогательного массива в отсортированный
            std::copy(output.begin(), output.end(), array.begin());
        };

        T max = *std::max_element(array.begin(), array.end());
        for (int exp = 1; max / exp > 0; exp *= 10) {
            countSort(exp);
        }
    }
} // namespace algo

#endif