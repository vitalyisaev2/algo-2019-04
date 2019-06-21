#ifndef SEQUENCE_GENERATOR_HPP
#define SEQUENCE_GENERATOR_HPP

#include <algorithm>
#include <map>
#include <random>

namespace utils
{

    template <typename T>
    class SequenceGenerator
    {
      public:
        SequenceGenerator() : generator((std::random_device())()){};

        enum Kind {
            Sorted             = 0,
            ReverseSorted      = 1,
            Shuffled100Percent = 2,
            Shuffled10Percent  = 3,
            Shuffled5Items     = 4,
        };

        // возвращаем последовательность случайных значений длиной N, равномерно распределённых от O до k
        std::vector<T> GetSequence(size_t n, T k, Kind kind)
        {
            std::vector<T> result;

            if (!sequences.contains(n)) {
                sequences[n] = std::map<T, std::map<Kind, std::vector<T>>>();
            }
            if (!sequences[n].contains(k)) {
                sequences[n][k] = std::map<Kind, std::vector<T>>();
            }
            if (!sequences[n][k].contains(kind)) {
                sequences[n][k][kind] = make_sequence(n, k, kind);
            }

            return sequences[n][k][kind];
        }

      private:
        std::vector<T> make_sorted_sequence(size_t n) const
        {
            std::vector<T> v(n);
            std::iota(std::begin(v), std::end(v), 0);
            return v;
        };

        std::vector<T> make_sequence(size_t n, T k, Kind kind)
        {
            auto                                  v = make_sorted_sequence(n);
            std::uniform_int_distribution<size_t> dist(0, n - 1);

            switch (kind) {
            case Sorted:
                break;
            case ReverseSorted:
                std::reverse(v.begin(), v.end());
                break;
            case Shuffled100Percent:
                std::shuffle(v.begin(), v.end(), generator);
                break;
            case Shuffled10Percent:
                for (size_t i = 0; i < n / 10; i++) {
                    size_t from = static_cast<size_t>(dist(generator));
                    size_t to   = static_cast<size_t>(dist(generator));
                    std::swap(v[from], v[to]);
                }
                break;
            case Shuffled5Items:
                for (size_t i = 0; i < 5; i++) {
                    size_t from = static_cast<size_t>(dist(generator));
                    size_t to   = static_cast<size_t>(dist(generator));
                    std::swap(v[from], v[to]);
                }
                break;
            default:
                throw "unknown sequence kind";
                break;
            }
            return v;
        }

        // размер последовательности -> верхняя планка равномерного распределения -> тип последовательности -> последовательность
        std::map<size_t, std::map<T, std::map<Kind, std::vector<T>>>> sequences;
        std::mt19937                                                  generator;
    };

} // namespace utils

#endif