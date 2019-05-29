#include "algebraic.hpp"
#include <benchmark/benchmark.h>
#include <functional>

using gcd_func = std::function<int(int, int)>;

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

static void BM_04_gcd_mod_recursive(benchmark::State& state)
{
    gcd(state, gcd_mod_recursive);
}

BENCHMARK(BM_04_gcd_sub)->RangeMultiplier(2)->Range(1 << 4, 1 << 18)->Complexity(benchmark::oN);
BENCHMARK(BM_04_gcd_mod)->RangeMultiplier(2)->Range(1 << 4, 1 << 18)->Complexity(benchmark::oN);
BENCHMARK(BM_04_gcd_mod_recursive)->RangeMultiplier(2)->Range(1 << 4, 1 << 18)->Complexity(benchmark::oN);