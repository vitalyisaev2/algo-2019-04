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
    auto section = [](power_func<int> f, const char* name) {
        SECTION(name)
        {
            REQUIRE(f(2, 10) == 1024);
        }
    };

    section(power_iterative<int>, "iterative");
    section(power_via_power_of_two<int>, "via power of two");
    section(power_via_exponent_binary_partition<int>, "via exponent binary partition");
#ifdef _GNUC_
    section(power_via_exponent_binary_partition_with_gcc_extentions<int>, "via exponent binary partition with GCC extentions");
#endif
}

TEST_CASE("Fibonacci")
{
    auto section = [](fibonacci_func<int, int> f, const char* name) {
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

    section(fibonacci_recursive<int, int>, "recursive");
    section(fibonacci_iterative<int, int>, "iterative");
    section(fibonacci_golden_ratio<int, int>, "golden_ratio");
    section(fibonacci_matrix<int, int>, "golden_ratio");
}