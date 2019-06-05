#include "algebraic.hpp"
#include <catch2/catch.hpp>
#include <cmath>
#include <tuple>

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
            REQUIRE(f(2, 2) == 4);
            REQUIRE(f(2, 10) == 1024);
            REQUIRE(f(3, 3) == 27);
            REQUIRE(f(4, 1) == 4);
        }
    };

    section(power_iterative<int>, "iterative");
    section(power_via_power_of_two<int>, "via power of two");
    section(power_via_exponent_binary_partition<int>, "via exponent binary partition");
    section(power_via_exponent_binary_partition_with_gcc_extentions<int>, "via exponent binary partition with GCC extentions");
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

TEST_CASE("Prime numbers")
{
    auto section = [](prime_numbers_func<uint> f, const char* name) {
        SECTION(name)
        {
            std::vector<std::tuple<uint, std::vector<uint>>> cases = {
                {0, {}},
                {1, {}},
                {2, {2}},
                {3, {2, 3}},
                {4, {2, 3}},
                {5, {2, 3, 5}},
                {6, {2, 3, 5}},
                {7, {2, 3, 5, 7}},
                {8, {2, 3, 5, 7}},
                {9, {2, 3, 5, 7}},
                {10, {2, 3, 5, 7}},
                {11, {2, 3, 5, 7, 11}},
                {30, {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}},
                {100, {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}},
            };

            for (const auto& c : cases) {
                auto              n = std::get<0>(c);
                std::vector<uint> actual;
                std::vector<uint> expected = std::get<1>(c);
                f(n, actual);
                REQUIRE(actual == expected);
            }
        }
    };

    section(prime_numbers_bruteforce<uint>, "bruteforce");
    section(prime_numbers_bruteforce_optimized<uint>, "bruteforce_optimized");
    // section(prime_numbers_eratosthenes_sieve<uint>, "eratosthenes_sieve");
}