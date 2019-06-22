#ifndef COUNTING_SORT_HPP
#define COUNTING_SORT_HPP

#include <algorithm>
#include <vector>

namespace algo
{

    template <typename T>
    void CountingSort(std::vector<T>& array)
    {
        if (array.size() < 2) {
            return;
        }

        // определяем максимальный и минимальный элементы массива
        T max_value = *std::max_element(array.begin(), array.end());
        T min_value = *std::min_element(array.begin(), array.end());

        // организуем массив счётчиков, инициализируем их нулями
        auto                total = static_cast<size_t>(max_value - min_value + 1);
        std::vector<size_t> counts(total, 0);
        for (size_t i = 0; i < array.size(); i++) {
            auto p = array[i] - min_value;
            counts[static_cast<size_t>(p)]++;
        }

        // преобразуем счётчики в массив кумулятивных сумм
        for (size_t i = 1; i < counts.size(); i++) {
            counts[i] = counts[i] + counts[i - 1];
        }

        // перезаписываем c обратной стороны данные в массив
        size_t p = array.size() - 1;
        for (size_t i = counts.size() - 1; i > 0; i--) {
            while (counts[i] != counts[i - 1]) {
                T value  = min_value + static_cast<T>(i);
                array[p] = value;
                p--;
                counts[i]--;
            }
        }

        // отдельно обрабатываем первый элемент
        while (counts[0] > 0) {
            array[p] = min_value;
            p--;
            counts[0]--;
        }
    }
} // namespace algo

#endif