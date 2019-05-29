#include "algebraic.hpp"
#include <catch2/catch.hpp>

TEST_CASE("Greatest common divisor")
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

TEST_CASE("Power")
{
    SECTION("iterative") {
        REQUIRE(power_iterative(2, 10) == 1024);
    }
    SECTION("binary") {
        REQUIRE(power_binary(2, 10) == 1024);
    }
}