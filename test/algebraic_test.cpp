#include "algebraic.hpp"
#include <catch2/catch.hpp>
#include <cmath>
#include <tuple>

TEST_CASE("GCD")
{
    SECTION("sub")
    {
        REQUIRE(algo::GCDSub(1071, 462) == 21);
    }

    SECTION("mod")
    {
        REQUIRE(algo::GCDMod(1071, 462) == 21);
    }
}

TEST_CASE("Exponentiation")
{
    auto section = [](algo::PowerFunc<int> f, const char* name) {
        SECTION(name)
        {
            REQUIRE(f(2, 2) == 4);
            REQUIRE(f(2, 10) == 1024);
            REQUIRE(f(3, 3) == 27);
            REQUIRE(f(4, 1) == 4);
        }
    };

    section(algo::PowerIterative<int>, "iterative");
    section(algo::PowerViaPowerOfTwo<int>, "via power of two");
    section(algo::PowerViaExponentBinaryPartition<int>, "via exponent binary partition");
    section(algo::PowerViaExponentBinaryPartitionV2<int>, "via exponent binary partition with GCC extentions");
    section(algo::PowerViaExponentBinaryPartition_fast<int>, "via exponent binary partition fast");
}

TEST_CASE("Fibonacci")
{
    auto section = [](algo::FibonacciFunc<int, int> f, const char* name) {
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

    section(algo::fibonacci_recursive<int, int>, "recursive");
    section(algo::FibonacciIterative<int, int>, "iterative");
    section(algo::FibonacciGoldenRatio<int, int>, "golden_ratio");
    section(algo::FibonacciMatrix<int, int>, "golden_ratio");
}

TEST_CASE("Prime numbers")
{
    auto section = [](algo::PrimeNumbersFunc<uint> f, const char* name) {
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

    section(algo::PrimeNumbersBruteforce<uint>, "bruteforce");
    section(algo::PrimeNumbersBruteforceOptimized<uint>, "bruteforce_optimized");
    section(algo::PrimeNumbersEratosthenesSieve<uint>, "eratosthenes_sieve");
}