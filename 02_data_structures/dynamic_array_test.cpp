#include "dynamic_array.hpp"
#include "single_array.hpp"
#include <catch2/catch.hpp>

TEST_CASE("DynamicArray")
{
    SECTION("SingleArray") {
        DynamicArray<int>* array = new SingleArray<int>();
        delete array;
    }
}