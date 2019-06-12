#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include "algebraic.hpp"

// Сортировка Шелла
template <typename Gen, typename T>
void shell_sort(std::vector<T>& data)
{
    Gen generator(data.size());
    while (generator.valid()) {
        auto gap = generator.next();
        for (auto i = gap; i < data.size(); i++) {
            auto tmp = data[i];
            auto j   = i;
            for (; j >= gap && data[j - gap] > tmp; j -= gap) {
                data[j] = data[j - gap];
            }
            data[j] = tmp;
        }
    }
}

// Фабрика различных вариантов сортировки Шелла
class ShellSortFactory
{
  public:
    enum Sequence {
        Default = 0,
    };

    template <typename T>
    sort_func<T> Get(Sequence seq)
    {
        switch (seq) {
        case Default:
            return shell_sort<DefaultSequence, T>;
        default:
            throw "illegal sequence";
        }
    }

  private:
    // Оригинальная последовательность промежутков, предложенная Шеллом (O(N^2) в худшем случае)
    class DefaultSequence
    {
      public:
        DefaultSequence(size_t _n) : n(_n), k(1){};

        bool valid() const
        {
            return n / power_via_exponent_binary_partition_fast<size_t>(2, k) > 0;
        }

        size_t next()
        {
            return n / power_via_exponent_binary_partition_fast<size_t>(2, k++);
        }

      private:
        size_t n;
        size_t k;
    };
};


#endif