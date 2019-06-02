#include "algebraic.hpp"
#include <benchmark/benchmark.h>
#include <functional>

// greatest common divisor

using gcd_func = std::function<long(long, int)>;

const int gcd_divisor = 8;

static void gcd(benchmark::State& state, gcd_func f)
{
    for (auto _ : state) {
        benchmark::DoNotOptimize(f(state.range(0), gcd_divisor));
    }
    state.SetComplexityN(state.range(0));
}

static void BM_04_gcd_sub(benchmark::State& state)
{
    gcd(state, gcd_sub);
}

static void BM_04_gcd_mod(benchmark::State& state)
{
    gcd(state, gcd_mod);
}

BENCHMARK(BM_04_gcd_sub)->RangeMultiplier(2)->Range(1 << 4, 1 << 18)->Complexity(benchmark::oN);
BENCHMARK(BM_04_gcd_mod)->RangeMultiplier(2)->Range(1 << 4, 1 << 18)->Complexity(benchmark::oN);

// power (exponentiation)

using power_func = std::function<int(int, int)>;

const int power_base = 2;

static void power(benchmark::State& state, power_func f)
{

    for (auto _ : state) {
        benchmark::DoNotOptimize(f(power_base, state.range(0)));
    }
    state.SetComplexityN(state.range(0));
}

static void BM_04_power_iterative(benchmark::State& state)
{
    power(state, power_iterative);
}

static void BM_04_power_via_power_of_two(benchmark::State& state)
{
    power(state, power_via_power_of_two);
}

static void BM_04_power_via_exponent_binary_partition(benchmark::State& state)
{
    power(state, power_via_exponent_binary_partition);
}

BENCHMARK(BM_04_power_iterative)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);
BENCHMARK(BM_04_power_via_power_of_two)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);
BENCHMARK(BM_04_power_via_exponent_binary_partition)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);