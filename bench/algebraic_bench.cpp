#include "algebraic.hpp"
#include <benchmark/benchmark.h>

// greatest common divisor

const int gcd_divisor = 8;

static void gcd(benchmark::State& state, algo::GCDFunc<int> f)
{
    for (auto _ : state) {
        benchmark::DoNotOptimize(f(state.range(0), gcd_divisor));
    }
    state.SetComplexityN(state.range(0));
}

static void BM_04_GCDSub(benchmark::State& state)
{
    gcd(state, algo::GCDSub<int>);
}

static void BM_04_GCDMod(benchmark::State& state)
{
    gcd(state, algo::GCDMod<int>);
}

BENCHMARK(BM_04_GCDSub)->RangeMultiplier(2)->Range(1 << 4, 1 << 18)->Complexity(benchmark::oN);
BENCHMARK(BM_04_GCDMod)->RangeMultiplier(2)->Range(1 << 4, 1 << 18)->Complexity(benchmark::oN);

// power (exponentiation)

const int power_base = 2;

static void power(benchmark::State& state, algo::PowerFunc<int> f)
{

    for (auto _ : state) {
        benchmark::DoNotOptimize(f(power_base, state.range(0)));
    }
    state.SetComplexityN(state.range(0));
}

static void BM_04_PowerIterative(benchmark::State& state)
{
    power(state, algo::PowerIterative<int>);
}

static void BM_04_PowerViaPowerOfTwo(benchmark::State& state)
{
    power(state, algo::PowerViaPowerOfTwo<int>);
}

static void BM_04_PowerViaExponentBinaryPartition(benchmark::State& state)
{
    power(state, algo::PowerViaExponentBinaryPartition<int>);
}

static void BM_04_PowerViaExponentBinaryPartitionV2(benchmark::State& state)
{
    power(state, algo::PowerViaExponentBinaryPartitionV2<int>);
}

static void BM_04_PowerViaExponentBinaryPartition_fast(benchmark::State& state)
{
    power(state, algo::PowerViaExponentBinaryPartition_fast<int>);
}

BENCHMARK(BM_04_PowerIterative)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);
BENCHMARK(BM_04_PowerViaPowerOfTwo)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);
BENCHMARK(BM_04_PowerViaExponentBinaryPartition)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);
BENCHMARK(BM_04_PowerViaExponentBinaryPartitionV2)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);
BENCHMARK(BM_04_PowerViaExponentBinaryPartition_fast)->RangeMultiplier(2)->Range(1 << 4, 1 << 20)->Complexity(benchmark::oN);

// fibonacci

static void fibonacci(benchmark::State& state, algo::FibonacciFunc<int, int> f)
{
    for (auto _ : state) {
        benchmark::DoNotOptimize(f(state.range(0)));
    }
    state.SetComplexityN(state.range(0));
}

static void BM_04_fibonacci_recursive(benchmark::State& state)
{
    fibonacci(state, algo::fibonacci_recursive<int, int>);
}

static void BM_04_FibonacciIterative(benchmark::State& state)
{
    fibonacci(state, algo::FibonacciIterative<int, int>);
}

static void BM_04_FibonacciGoldenRatio(benchmark::State& state)
{
    fibonacci(state, algo::FibonacciGoldenRatio<int, int>);
}

static void BM_04_FibonacciMatrix(benchmark::State& state)
{
    fibonacci(state, algo::FibonacciMatrix<int, int>);
}

BENCHMARK(BM_04_fibonacci_recursive)->Arg(1)->Arg(5)->Arg(10)->Arg(20)->Arg(30)->Complexity(benchmark::oN);
BENCHMARK(BM_04_FibonacciIterative)
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
BENCHMARK(BM_04_FibonacciGoldenRatio)
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
BENCHMARK(BM_04_FibonacciMatrix)
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

static void prime_numbers(benchmark::State& state, algo::PrimeNumbersFunc<uint> f)
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

static void BM_04_PrimeNumbersBruteforce(benchmark::State& state)
{
    prime_numbers(state, algo::PrimeNumbersBruteforce<uint>);
}

static void BM_04_PrimeNumbersBruteforce_optimized(benchmark::State& state)
{
    prime_numbers(state, algo::PrimeNumbersBruteforceOptimized<uint>);
}

static void BM_04_PrimeNumbersEratosthenesSieve(benchmark::State& state)
{
    prime_numbers(state, algo::PrimeNumbersEratosthenesSieve<uint>);
}

BENCHMARK(BM_04_PrimeNumbersBruteforce)
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

BENCHMARK(BM_04_PrimeNumbersBruteforce_optimized)
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

BENCHMARK(BM_04_PrimeNumbersEratosthenesSieve)
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