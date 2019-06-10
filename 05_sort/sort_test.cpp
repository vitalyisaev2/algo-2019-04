#include "insertion.hpp"
#include "sequence_generator.hpp"
#include <catch2/catch.hpp>

SequenceGenerator<int> generator;

TEST_CASE("sort")
{
    auto section = [](sort_func<int> f, const char* name) {
        SECTION(name)
        {
            SECTION("sorted sequence")
            {
                {
                    auto             input = generator.GetSequence(10, SequenceGenerator<int>::Sorted);
                    std::vector<int> expected(input);
                    f(input);
                    REQUIRE(input == expected);
                }
            }
            SECTION("reverse sorted sequence")
            {
                {
                    std::vector<int> input(generator.GetSequence(10, SequenceGenerator<int>::ReverseSorted));
                    std::vector<int> expected(input.size());
                    std::reverse_copy(input.begin(), input.end(), expected.begin());
                    f(input);
                    REQUIRE(input == expected);
                }
            }
        }
    };

    section(insertion_sort<int>, "insertion sort");
}