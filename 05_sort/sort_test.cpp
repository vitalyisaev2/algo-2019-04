#include "insertion_sort.hpp"
#include "shell_sort.hpp"
#include "sequence_generator.hpp"
#include <catch2/catch.hpp>

SequenceGenerator<int> sequenceGenerator;
ShellSortFactory shellSortFactory;

TEST_CASE("sort")
{
    auto section = [](sort_func<int> f, const char* name) {
        SECTION(name)
        {
            SECTION("sorted sequence")
            {
                {
                    auto             input = sequenceGenerator.GetSequence(8, SequenceGenerator<int>::Sorted);
                    std::vector<int> expected(input);
                    f(input);
                    REQUIRE(input == expected);
                }
            }
            SECTION("reverse sorted sequence")
            {
                {
                    std::vector<int> input(sequenceGenerator.GetSequence(8, SequenceGenerator<int>::ReverseSorted));
                    std::vector<int> expected(input.size());
                    std::reverse_copy(input.begin(), input.end(), expected.begin());
                    f(input);
                    REQUIRE(input == expected);
                }
            }

            SECTION("shuffled sequence")
            {
                {
                    std::vector<int> input(sequenceGenerator.GetSequence(8, SequenceGenerator<int>::Shuffled100Percent));
                    std::vector<int> expected(input.size());
                    std::copy(input.begin(), input.end(), expected.begin());
                    std::sort(expected.begin(), expected.end());
                    f(input);
                    REQUIRE(input == expected);
                }
            }
        }
    };

    section(insertion_sort<int>, "insertion sort");
    section(shellSortFactory.Get<int>(ShellSortFactory::Sequence::Default), "shell sort (default sequence)");
}