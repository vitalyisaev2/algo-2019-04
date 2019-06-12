#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP

#include "algebraic.hpp"
#include <iostream>

namespace algo
{

    // Сортировка Шелла
    template <typename Gen, typename T>
    void ShellSort(std::vector<T>& data)
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
            Shell     = 0,
            Sedgewick = 1,
            Ciura     = 2,
        };

        template <typename T>
        algo::SortFunc<T> Get(Sequence seq)
        {
            switch (seq) {
            case Shell:
                return ShellSort<ShellSequence, T>;
            case Sedgewick:
                return ShellSort<SedgewickSequence, T>;
            case Ciura:
                return ShellSort<CiuraSequence, T>;
            default:
                throw "illegal sequence";
            }
        }

      private:
        // Оригинальная последовательность промежутков, предложенная Шеллом в 1959 (O(N^2) в худшем случае)
        class ShellSequence
        {
          public:
            ShellSequence(size_t _n) : n(_n), k(1){};

            bool valid() const
            {
                return n / algo::PowerViaExponentBinaryPartition_fast<size_t>(2, k) > 0;
            }

            size_t next()
            {
                return n / algo::PowerViaExponentBinaryPartition_fast<size_t>(2, k++);
            }

          private:
            size_t n;
            size_t k;
        };

        // Последовательность Седжвика, предложенная в 1971 г. (O(N^4/3) в худшем случае)
        class SedgewickSequence
        {
          public:
            SedgewickSequence(size_t n)
            {
                for (size_t k = 1, gap = 1; gap < n / 2; k++) {
                    gaps.push_back(gap);
                    // 4^k + 3*2^(k-1) + 1
                    gap = algo::PowerViaExponentBinaryPartition_fast<size_t>(4, k) +
                          algo::PowerViaExponentBinaryPartition_fast<size_t>(2, k - 1) * 3 + 1;
                }
                it = gaps.rbegin();
            }

            bool valid() const
            {
                return it != gaps.rend();
            }

            size_t next()
            {
                return *(it++);
            }

          private:
            std::vector<size_t>                         gaps;
            std::vector<size_t>::const_reverse_iterator it;
        };

        // Эмпирическая последовательность Ciura (2001), считается лучшей, асимптотика не установлена
        class CiuraSequence
        {
          public:
            CiuraSequence(size_t n) : gaps({1, 4, 10, 23, 57, 132, 301, 701})
            {
                // числа последовательности выще k=8 не определены, но, согласно Википедии,
                // их можно доопределить с помощью рекурентного соотношения
                if (n > 2 * gaps.back()) {
                    while (true) {
                        size_t gap = static_cast<size_t>(float(gap) * 2.25);
                        if (n < 2 * gap) {
                            break;
                        }
                        gaps.push_back(gap);
                    }
                    it = gaps.rbegin();
                } else {
                    // определяем следующий подходящий интервал
                    it = gaps.rbegin();
                    for (size_t i = gaps.size() - 1; i > 0; i--) {
                        if (gaps[i] < n / 2) {
                            std::advance(it, i);
                            return;
                        }
                    }
                }
            };
            bool valid() const
            {
                return it != gaps.rend();
            }
            size_t next()
            {
                return *(it++);
            }

          private:
            std::vector<size_t>                         gaps;
            std::vector<size_t>::const_reverse_iterator it;
        };
    };

} // namespace algo

#endif