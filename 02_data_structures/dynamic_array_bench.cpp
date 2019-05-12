#include "factor_array.hpp"
#include "matrix_array.hpp"
#include "single_array.hpp"
#include "vector_array.hpp"
#include <benchmark/benchmark.h>

const int iterations = 2 << 10;

template <typename T>
static void addFront(benchmark::State& state, DynamicArray<T>* array)
{
    const T value = 1;
    for (auto _ : state) {
        for (auto i = 0; i < iterations; i++) {
            array->add(value, 0);
        }
    }
}

template <typename T>
static void addBack(benchmark::State& state, DynamicArray<T>* array)
{
    const T value = 1;
    for (auto _ : state) {
        for (auto i = 0; i < iterations; i++) {
            array->add(value);
        }
    }
}

template <typename T>
static void removeFront(benchmark::State& state, DynamicArray<T>* array)
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
static void removeBack(benchmark::State& state, DynamicArray<T>* array)
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

// add front

static void BM_SingleArray_Add_Front(benchmark::State& state)
{
    SingleArray<int> array;
    addFront<int>(state, &array);
}

static void BM_VectorArray_Add_Front(benchmark::State& state)
{
    VectorArray<int> array(static_cast<size_t>(state.range(0)));
    addFront<int>(state, &array);
}

static void BM_FactorArray_Add_Front(benchmark::State& state)
{
    FactorArray<int> array;
    addFront<int>(state, &array);
}

static void BM_MatrixArray_Add_Front(benchmark::State& state)
{
    MatrixArray<int> array(static_cast<size_t>(state.range(0)));
    addFront<int>(state, &array);
}

// add back

static void BM_SingleArray_Add_Back(benchmark::State& state)
{
    SingleArray<int> array;
    addBack<int>(state, &array);
}

static void BM_VectorArray_Add_Back(benchmark::State& state)
{
    VectorArray<int> array(static_cast<size_t>(state.range(0)));
    addBack<int>(state, &array);
}

static void BM_FactorArray_Add_Back(benchmark::State& state)
{
    FactorArray<int> array;
    addBack<int>(state, &array);
}

static void BM_MatrixArray_Add_Back(benchmark::State& state)
{
    MatrixArray<int> array(static_cast<size_t>(state.range(0)));
    addBack<int>(state, &array);
}

// remove front

static void BM_SingleArray_Remove_Front(benchmark::State& state)
{
    SingleArray<int> array;
    removeFront<int>(state, &array);
}

static void BM_VectorArray_Remove_Front(benchmark::State& state)
{
    VectorArray<int> array(static_cast<size_t>(state.range(0)));
    removeFront<int>(state, &array);
}

static void BM_FactorArray_Remove_Front(benchmark::State& state)
{
    FactorArray<int> array;
    removeFront<int>(state, &array);
}

// remove back

static void BM_SingleArray_Remove_Back(benchmark::State& state)
{
    SingleArray<int> array;
    removeBack<int>(state, &array);
}

static void BM_VectorArray_Remove_Back(benchmark::State& state)
{
    VectorArray<int> array(static_cast<size_t>(state.range(0)));
    removeBack<int>(state, &array);
}

static void BM_FactorArray_Remove_Back(benchmark::State& state)
{
    FactorArray<int> array;
    removeBack<int>(state, &array);
}

BENCHMARK(BM_SingleArray_Add_Front);
BENCHMARK(BM_VectorArray_Add_Front)->RangeMultiplier(2)->Arg(2 << 0)->Arg(2 << 5)->Arg(2 << 10);
BENCHMARK(BM_FactorArray_Add_Front);
BENCHMARK(BM_MatrixArray_Add_Front)->RangeMultiplier(2)->Arg(2 << 0)->Arg(2 << 5)->Arg(2 << 10);
BENCHMARK(BM_SingleArray_Add_Back);
BENCHMARK(BM_VectorArray_Add_Back)->RangeMultiplier(2)->Arg(2 << 0)->Arg(2 << 5)->Arg(2 << 10);
BENCHMARK(BM_FactorArray_Add_Back);
BENCHMARK(BM_MatrixArray_Add_Back)->RangeMultiplier(2)->Arg(2 << 0)->Arg(2 << 5)->Arg(2 << 10);
BENCHMARK(BM_SingleArray_Remove_Front);
BENCHMARK(BM_VectorArray_Remove_Front)->RangeMultiplier(2)->Arg(2 << 0)->Arg(2 << 5)->Arg(2 << 10);
BENCHMARK(BM_FactorArray_Remove_Front);
BENCHMARK(BM_SingleArray_Remove_Back);
BENCHMARK(BM_VectorArray_Remove_Back)->RangeMultiplier(2)->Arg(2 << 0)->Arg(2 << 5)->Arg(2 << 10);
BENCHMARK(BM_FactorArray_Remove_Back);