#include "algebraic.hpp"
#include <catch2/catch.hpp>

TEST_CASE("GCD")
{
    SECTION("sub")
    {
        REQUIRE(gcd_sub(1071, 462) == 21);
    }

    SECTION("mod")
    {
        REQUIRE(gcd_mod(1071, 462) == 21);
    }
}

TEST_CASE("Exponentiation")
{
    SECTION("iterative")
    {
        REQUIRE(power_iterative(2, 10) == 1024);
    }
    SECTION("via power of two")
    {
        REQUIRE(power_via_power_of_two(2, 10) == 1024);
    }
    SECTION("via exponent binary partition")
    {
        REQUIRE(power_via_exponent_binary_partition(2, 10) == 1024);
    }
}