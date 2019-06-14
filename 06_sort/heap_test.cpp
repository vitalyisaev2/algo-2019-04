#include "heap.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Heap")
{
    SECTION("BuildHeap")
    {
        std::vector<int> input({9, 5, 10, 8, 2, 1, 0, 3, 11, 4, 6, 7});
        algo::HeapBuild<int>(input);
        std::vector<int> expected({11, 9, 10, 8, 6, 7, 0, 3, 5, 4, 2, 1});
        REQUIRE(input == expected);
    }
}