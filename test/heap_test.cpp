#include "heap.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Heap")
{
    SECTION("Build")
    {
        std::vector<int> input({9, 5, 10, 8, 2, 1, 0, 3, 11, 4, 6, 7});
        algo::HeapBuild<int>(input);
        std::vector<int> expected({11, 9, 10, 8, 6, 7, 0, 3, 5, 4, 2, 1});
        REQUIRE(input == expected);
    }

    SECTION("RemoveMax")
    {
        std::vector<int> input({11, 9, 10, 8, 6, 7, 0, 3, 5, 4, 2, 1});
        auto             value = algo::HeapRemoveMax<int>(input);
        REQUIRE(value == 11);
        std::vector<int> expected({10, 9, 7, 8, 6, 1, 0, 3, 5, 4, 2});
        REQUIRE(input == expected);
    }

    SECTION("Insert")
    {
        std::vector<int> input({11, 9, 10, 8, 6, 7, 0, 3, 5, 4, 2, 1});
        algo::HeapInsert(input, 11);
        std::vector<int> expected({11, 9, 11, 8, 6, 10, 0, 3, 5, 4, 2, 1, 7});
        REQUIRE(input == expected);
    }
}