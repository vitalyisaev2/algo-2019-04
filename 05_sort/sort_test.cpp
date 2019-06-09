#include "insertion.hpp"
#include <catch2/catch.hpp>

TEST_CASE("sort")
{
    auto section = [](sort_func<int> f, const char* name) {
        SECTION(name)
        {
            SECTION("sorted sequence")
            {
                {
                    std::vector<int> input    = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                    std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                    f(input);
                    REQUIRE(input == expected);
                }
            }
            SECTION("reverse sorted sequence")
            {
                {
                    std::vector<int> input    = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
                    std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
                    f(input);
                    REQUIRE(input == expected);
                }
            }
        }
    };

    section(insertion_sort<int>, "insertion sort");
}