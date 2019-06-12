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

        std::vector<T> GetSequence(size_t n, Kind kind)
        {
            std::vector<T> result;
            if (sequences.contains(n)) {
                auto size_sequences = sequences[n];
                if (size_sequences.contains(kind)) {
                    // отдать кешированное значение
                    result = size_sequences[kind];
                } else {
                    // сгенерировать последовательность и сохранить её в кеше
                    result             = make_sequence(n, kind);
                    sequences[n][kind] = result;
                }
            } else {
                result             = make_sequence(n, kind);
                sequences[n][kind] = result;
            }

            // копируем массив, чтобы клиент мог изменять копию
            return result;
        }

      private:
        std::vector<T> make_sorted_sequence(size_t n) const
        {
            std::vector<T> v(n);
            std::iota(std::begin(v), std::end(v), 0);
            return v;
        };

        std::vector<T> make_sequence(size_t n, Kind kind)
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
                throw "unknow sequence kind";
                break;
            }
            return v;
        }

        std::map<size_t, std::map<int, std::vector<T>>> sequences;
        std::mt19937                                    generator;
    };

} // namespace utils

#endif