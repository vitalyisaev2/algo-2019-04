#include "insertion_sort.hpp"
#include "sequence_generator.hpp"
#include "shell_sort.hpp"
#include <catch2/catch.hpp>

TEST_CASE("sort")
{

    SequenceGenerator<int> sequenceGenerator;
    ShellSortFactory       shellSortFactory;

    auto section = [&](sort_func<int> f, const char* name) {
        SECTION(name)
        {
            SECTION("empty array")
            {
                std::vector<int> input;
                std::vector<int> expected;
                f(input);
                REQUIRE(input == expected);
            }
            SECTION("one element array")
            {
                std::vector<int> input({1});
                std::vector<int> expected({1});
                f(input);
                REQUIRE(input == expected);
            }
            SECTION("sorted sequence")
            {
                auto             input = sequenceGenerator.GetSequence(32, SequenceGenerator<int>::Sorted);
                std::vector<int> expected(input);
                f(input);
                REQUIRE(input == expected);
            }
            SECTION("reverse sorted sequence")
            {
                std::vector<int> input(sequenceGenerator.GetSequence(32, SequenceGenerator<int>::ReverseSorted));
                std::vector<int> expected(input.size());
                std::reverse_copy(input.begin(), input.end(), expected.begin());
                f(input);
                REQUIRE(input == expected);
            }

            SECTION("shuffled sequence")
            {
                std::vector<int> input(sequenceGenerator.GetSequence(32, SequenceGenerator<int>::Shuffled100Percent));
                std::vector<int> expected(input.size());
                std::copy(input.begin(), input.end(), expected.begin());
                std::sort(expected.begin(), expected.end());
                f(input);
                REQUIRE(input == expected);
            }
        }
    };

    section(insertion_sort<int>, "insertion sort");
    section(shellSortFactory.Get<int>(ShellSortFactory::Sequence::Shell), "shell sort (Shell sequence)");
    section(shellSortFactory.Get<int>(ShellSortFactory::Sequence::Sedgewick), "shell sort (Sedgewick sequence)");
    section(shellSortFactory.Get<int>(ShellSortFactory::Sequence::Ciura), "shell sort (Ciura sequence)");
}