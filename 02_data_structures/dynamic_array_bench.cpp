#include "factor_array.hpp"
#include "matrix_array.hpp"
#include "single_array.hpp"
#include "std_vector_array.hpp"
#include "vector_array.hpp"
#include <benchmark/benchmark.h>
#include <vector>

template <typename T>
static void addFront(benchmark::State& state, DynamicArray<T>* array, int iterations)
{
    const T value = 1;
    for (auto _ : state) {
        for (auto i = 0; i < iterations; i++) {
            array->add(value, 0);
        }
    }
}

template <typename T>
static void addBack(benchmark::State& state, DynamicArray<T>* array, int iterations)
{
    const T value = 1;
    for (auto _ : state) {
        for (auto i = 0; i < iterations; i++) {
            array->add(value);
        }
    }
}

template <typename T>
static void removeFront(benchmark::State& state, DynamicArray<T>* array, int iterations)
{
    for (auto _ : state) {
        state.PauseTiming();
        for (auto i = 0; i < iterations; i++) {
            array->add(i);
        }
        state.ResumeTiming();
        for (auto i = 0; i < iterations; i++) {
            array->remove(0);
        }
    }
}

template <typename T>
static void removeBack(benchmark::State& state, DynamicArray<T>* array, int iterations)
{
    for (auto _ : state) {
        state.PauseTiming();
        for (auto i = 0; i < iterations; i++) {
            array->add(i);
        }
        state.ResumeTiming();
        for (auto i = 0; i < iterations; i++) {
            array->remove(array->size() - 1);
        }
    }
}

template <typename T>
static void get(benchmark::State& state, DynamicArray<T>* array, int iterations)
{
    for (auto i = 0; i < iterations; i++) {
        array->add(i);
    }
    T val;
    for (auto _ : state) {
        for (auto i = 0; i < iterations; i++) {
            val = array->get(size_t(i));
        }
    }
}

// add front

template <typename T>
static void BM_DynamicArray_AddFront_Simple(benchmark::State& state)
{
    T array;
    addFront<int>(state, &array, state.range(0));
}

template <typename T>
static void BM_DynamicArray_AddFront_Parametrized(benchmark::State& state)
{
    T array(static_cast<size_t>(state.range(1)));
    addFront<int>(state, &array, state.range(0));
}

// add back

template <typename T>
static void BM_DynamicArray_AddBack_Simple(benchmark::State& state)
{
    T array;
    addBack<int>(state, &array, state.range(0));
}

template <typename T>
static void BM_DynamicArray_AddBack_Parametrized(benchmark::State& state)
{
    T array(static_cast<size_t>(state.range(1)));
    addBack<int>(state, &array, state.range(0));
}

// remove front

template <typename T>
static void BM_DynamicArray_RemoveFront_Simple(benchmark::State& state)
{
    T array;
    removeFront<int>(state, &array, state.range(0));
}

template <typename T>
static void BM_DynamicArray_RemoveFront_Parametrized(benchmark::State& state)
{
    T array(static_cast<size_t>(state.range(1)));
    removeFront<int>(state, &array, state.range(0));
}

// remove back

template <typename T>
static void BM_DynamicArray_RemoveBack_Simple(benchmark::State& state)
{
    T array;
    removeBack<int>(state, &array, state.range(0));
}

template <typename T>
static void BM_DynamicArray_RemoveBack_Parametrized(benchmark::State& state)
{
    T array(static_cast<size_t>(state.range(1)));
    removeBack<int>(state, &array, state.range(0));
}

// get

template <typename T>
static void BM_DynamicArray_Get_Simple(benchmark::State& state)
{
    T array;
    get<int>(state, &array, state.range(0));
}

template <typename T>
static void BM_DynamicArray_Get_Parametrized(benchmark::State& state)
{
    T array(static_cast<size_t>(state.range(1)));
    get<int>(state, &array, state.range(0));
}

// benchmark options

std::vector<int> iteration_values = {2 << 0, 2 << 4, 2 << 8, 2 << 12, 2 << 16};
std::vector<int> parameter_values = {2 << 1, 2 << 16};

static void OnePositionArgs(benchmark::internal::Benchmark* b)
{
    for (auto iterations : iteration_values) {
        b->Arg({iterations});
    }
}

static void TwoPositionArgs(benchmark::internal::Benchmark* b)
{
    for (auto iterations : iteration_values) {
        for (auto parameter : parameter_values) {
            b->Args({iterations, parameter});
        }
    }
}

BENCHMARK_TEMPLATE(BM_DynamicArray_AddFront_Simple, SingleArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_AddFront_Simple, VectorArray<int>)->Apply(TwoPositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_AddFront_Simple, FactorArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_AddFront_Simple, StdVectorArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_AddFront_Simple, MatrixArray<int>)->Apply(TwoPositionArgs);

BENCHMARK_TEMPLATE(BM_DynamicArray_AddBack_Simple, SingleArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_AddBack_Simple, VectorArray<int>)->Apply(TwoPositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_AddBack_Simple, FactorArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_AddBack_Simple, StdVectorArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_AddBack_Simple, MatrixArray<int>)->Apply(TwoPositionArgs);

BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveFront_Simple, SingleArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveFront_Simple, VectorArray<int>)->Apply(TwoPositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveFront_Simple, FactorArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveFront_Simple, StdVectorArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveFront_Simple, MatrixArray<int>)->Apply(TwoPositionArgs);

BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveBack_Simple, SingleArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveBack_Simple, VectorArray<int>)->Apply(TwoPositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveBack_Simple, FactorArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveBack_Simple, StdVectorArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveBack_Simple, MatrixArray<int>)->Apply(TwoPositionArgs);

BENCHMARK_TEMPLATE(BM_DynamicArray_Get_Simple, SingleArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_Get_Simple, VectorArray<int>)->Apply(TwoPositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_Get_Simple, FactorArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_Get_Simple, StdVectorArray<int>)->Apply(OnePositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_Get_Simple, MatrixArray<int>)->Apply(TwoPositionArgs);