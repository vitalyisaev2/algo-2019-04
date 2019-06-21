#include "common_sort.hpp"
#include "counting_sort.hpp"
#include "heap_sort.hpp"
#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "sequence_generator.hpp"
#include "shell_sort.hpp"
#include <catch2/catch.hpp>

TEST_CASE("sort")
{

    utils::SequenceGenerator<int> sequenceGenerator;
    algo::ShellSortFactory        shellSortFactory;

    auto section = [&](algo::SortFunc<int> f, const char* name) {
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
            SECTION("two element array")
            {
                std::vector<int> input({2, 1});
                std::vector<int> expected({1, 2});
                f(input);
                REQUIRE(input == expected);
            }
            SECTION("three element array")
            {
                std::vector<int> input({3, 2, 1});
                std::vector<int> expected({1, 2, 3});
                f(input);
                REQUIRE(input == expected);
            }
            SECTION("sorted sequence")
            {
                auto             input = sequenceGenerator.GetSequence(32, utils::SequenceGenerator<int>::Sorted);
                std::vector<int> expected(input);
                f(input);
                REQUIRE(input == expected);
            }
            SECTION("reverse sorted sequence")
            {
                std::vector<int> input(sequenceGenerator.GetSequence(32, utils::SequenceGenerator<int>::ReverseSorted));
                std::vector<int> expected(input.size());
                std::reverse_copy(input.begin(), input.end(), expected.begin());
                f(input);
                REQUIRE(input == expected);
            }

            SECTION("shuffled sequence")
            {
                std::vector<int> input(sequenceGenerator.GetSequence(32, utils::SequenceGenerator<int>::Shuffled100Percent));
                std::vector<int> expected(input.size());
                std::copy(input.begin(), input.end(), expected.begin());
                std::sort(expected.begin(), expected.end());
                f(input);
                REQUIRE(input == expected);
            }

            SECTION("repeated sequence")
            {
                std::vector<int> input({2, 3, 4, 2, 3, 4, 5});
                std::vector<int> expected({2, 2, 3, 3, 4, 4, 5});
                f(input);
                REQUIRE(input == expected);
            }
        }
    };

    section(algo::InsertionSort<int>, "insertion sort");
    section(shellSortFactory.Get<int>(algo::ShellSortFactory::Sequence::Shell), "shell sort (Shell sequence)");
    section(shellSortFactory.Get<int>(algo::ShellSortFactory::Sequence::Sedgewick), "shell sort (Sedgewick sequence)");
    section(shellSortFactory.Get<int>(algo::ShellSortFactory::Sequence::Ciura), "shell sort (Ciura sequence)");
    section(algo::HeapSort<int>, "heap sort");
    section(algo::MergeSort<int>, "merge sort");
    section(algo::QuickSort<int>, "quick sort");
    section(algo::CountingSort<int>, "counting sort");
}