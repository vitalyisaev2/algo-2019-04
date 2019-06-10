#include "algebraic.hpp"
#include <benchmark/benchmark.h>

// greatest common divisor

const int gcd_divisor = 8;

static void gcd(benchmark::State& state, gcd_func<int> f)
{
    for (auto _ : state) {
        benchmark::DoNotOptimize(f(state.range(0), gcd_divisor));
    }
    state.SetComplexityN(state.range(0));
}

static void BM_04_gcd_sub(benchmark::State& state)
{
    gcd(state, gcd_sub<int>);
}

static void BM_04_gcd_mod(benchmark::State& state)
{
    gcd(state, gcd_mod<int>);
}

BENCHMARK(BM_04_gcd_sub)->RangeMultiplier(2)->Range(1 << 4, 1 << 18)->Complexity(benchmark::oN);
BENCHMARK(BM_04_gcd_mod)->RangeMultiplier(2)->Range(1 << 4, 1 << 18)->Complexity(benchmark::oN);

// power (exponentiation)

const int power_base = 2;

static void power(benchmark::State& state, power_func<int> f)
{

    for (auto _ : state) {
        benchmark::DoNotOptimize(f(power_base, state.range(0)));
    }
    state.SetComplexityN(state.range(0));
}

static void BM_04_power_iterative(benchmark::State& state)
{
    power(state, power_iterative<int>);
}

static void BM_04_power_via_power_of_two(benchmark::State& state)
{
    power(state, power_via_power_of_two<int>);
}

static void BM_04_power_via_exponent_binary_partition(benchmark::State& state)
{
    power(state, power_via_exponent_binary_partition<int>);
}

static void BM_04_power_via_exponent_binary_partition_with_gcc_extentions(benchmark::State& state)
{
    power(state, power_via_exponent_binary_partition_with_gcc_extentions<int>);
}

static void BM_04_power_via_exponent_binary_partition_fast(benchmark::State& state)
{
    power(state, power_via_exponent_binary_partition_fast<int>);
}

BENCHMARK(BM_04_power_iterative)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);
BENCHMARK(BM_04_power_via_power_of_two)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);
BENCHMARK(BM_04_power_via_exponent_binary_partition)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);
BENCHMARK(BM_04_power_via_exponent_binary_partition_with_gcc_extentions)
    ->RangeMultiplier(2)
    ->Range(1 << 4, 1 << 20)
    ->Complexity(benchmark::oN);
BENCHMARK(BM_04_power_via_exponent_binary_partition_fast)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);

// fibonacci

static void fibonacci(benchmark::State& state, fibonacci_func<int, int> f)
{
    for (auto _ : state) {
        benchmark::DoNotOptimize(f(state.range(0)));
    }
    state.SetComplexityN(state.range(0));
}

static void BM_04_fibonacci_recursive(benchmark::State& state)
{
    fibonacci(state, fibonacci_recursive<int, int>);
}

static void BM_04_fibonacci_iterative(benchmark::State& state)
{
    fibonacci(state, fibonacci_iterative<int, int>);
}

static void BM_04_fibonacci_golden_ratio(benchmark::State& state)
{
    fibonacci(state, fibonacci_golden_ratio<int, int>);
}

static void BM_04_fibonacci_matrix(benchmark::State& state)
{
    fibonacci(state, fibonacci_matrix<int, int>);
}

BENCHMARK(BM_04_fibonacci_recursive)->Arg(1)->Arg(5)->Arg(10)->Arg(20)->Arg(30)->Complexity(benchmark::oN);
BENCHMARK(BM_04_fibonacci_iterative)
    ->Arg(1)
    ->Arg(5)
    ->Arg(10)
    ->Arg(20)
    ->Arg(30)
    ->Arg(50)
    ->Arg(100)
    ->Arg(500)
    ->Arg(1000)
    ->Complexity(benchmark::oN);
BENCHMARK(BM_04_fibonacci_golden_ratio)
    ->Arg(1)
    ->Arg(5)
    ->Arg(10)
    ->Arg(20)
    ->Arg(30)
    ->Arg(50)
    ->Arg(100)
    ->Arg(500)
    ->Arg(1000)
    ->Complexity(benchmark::oN);
BENCHMARK(BM_04_fibonacci_matrix)
    ->Arg(1)
    ->Arg(5)
    ->Arg(10)
    ->Arg(20)
    ->Arg(30)
    ->Arg(50)
    ->Arg(100)
    ->Arg(500)
    ->Arg(1000)
    ->Complexity(benchmark::oN);

// prime numbers

static void prime_numbers(benchmark::State& state, prime_numbers_func<uint> f)
{
    std::vector<uint> rcv;
    for (auto _ : state) {
        state.PauseTiming();
        rcv.clear();
        state.ResumeTiming();
        f(state.range(0), rcv);
    }
    state.SetComplexityN(state.range(0));
}

static void BM_04_prime_numbers_bruteforce(benchmark::State& state)
{
    prime_numbers(state, prime_numbers_bruteforce<uint>);
}

static void BM_04_prime_numbers_bruteforce_optimized(benchmark::State& state)
{
    prime_numbers(state, prime_numbers_bruteforce_optimized<uint>);
}

static void BM_04_prime_numbers_eratosthenes_sieve(benchmark::State& state)
{
    prime_numbers(state, prime_numbers_eratosthenes_sieve<uint>);
}

BENCHMARK(BM_04_prime_numbers_bruteforce)
    ->Arg(1)
    ->Arg(5)
    ->Arg(10)
    ->Arg(20)
    ->Arg(30)
    ->Arg(50)
    ->Arg(100)
    ->Arg(500)
    ->Arg(1000)
    ->Arg(5000)
    ->Arg(10000)
    ->Complexity(benchmark::oN);

BENCHMARK(BM_04_prime_numbers_bruteforce_optimized)
    ->Arg(1)
    ->Arg(5)
    ->Arg(10)
    ->Arg(20)
    ->Arg(30)
    ->Arg(50)
    ->Arg(100)
    ->Arg(500)
    ->Arg(1000)
    ->Arg(5000)
    ->Arg(10000)
    ->Arg(50000)
    ->Arg(100000)
    ->Complexity(benchmark::oN);

BENCHMARK(BM_04_prime_numbers_eratosthenes_sieve)
    ->Arg(1)
    ->Arg(5)
    ->Arg(10)
    ->Arg(20)
    ->Arg(30)
    ->Arg(50)
    ->Arg(100)
    ->Arg(500)
    ->Arg(1000)
    ->Arg(5000)
    ->Arg(10000)
    ->Arg(50000)
    ->Arg(100000)
    ->Complexity(benchmark::oN);