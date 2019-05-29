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

    SECTION("mod_recursive")
    {
        REQUIRE(gcd_mod_recursive(1071, 462) == 21);
    }
}