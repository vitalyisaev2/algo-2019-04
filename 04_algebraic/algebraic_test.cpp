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

TEST_CASE("Exponentiation"){SECTION("iterative"){REQUIRE(power_iterative(2, 10) == 1024);
}
SECTION("via power of two")
{
    REQUIRE(power_via_power_of_two(2, 10) == 1024);
}
SECTION("via exponent binary partition")
{
    REQUIRE(power_via_exponent_binary_partition(2, 10) == 1024);
}
#ifdef _GNUC_
SECTION("via exponent binary partition")
{
    REQUIRE(power_via_exponent_binary_partition_with_gcc_extentions(2, 10) == 1024);
}
#endif
}

TEST_CASE("Fibonacci")
{
    using func = std::function<int(int)>;

    auto section = [](func f, const char* name) {
        SECTION(name)
        {
            REQUIRE(f(0) == 0);
            REQUIRE(f(1) == 1);
            REQUIRE(f(2) == 1);
            REQUIRE(f(3) == 2);
            REQUIRE(f(4) == 3);
            REQUIRE(f(5) == 5);
            REQUIRE(f(6) == 8);
            REQUIRE(f(7) == 13);
            REQUIRE(f(8) == 21);
            REQUIRE(f(9) == 34);
        }
    };

    section(fibonacci_recursive, "recursive");
    section(fibonacci_iterative, "iterative");
    section(fibonacci_golden_ratio, "golden_ratio");
}