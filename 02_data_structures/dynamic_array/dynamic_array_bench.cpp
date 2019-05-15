#include "factor_array.hpp"
#include "matrix_array.hpp"
#include "single_array.hpp"
#include "std_vector_array.hpp"
#include "vector_array.hpp"
#include <benchmark/benchmark.h>
#include <vector>

template <typename T>
static void addFront(benchmark::State& state, DynamicArray<T>* array)
{
    for (auto i = 0; i < state.range(0); i++) {
        array->add(i);
    }
    const T value = 1;
    for (auto _ : state) {
        array->add(value, 0);
    }
    state.SetComplexityN(state.range(0));
}

template <typename T>
static void addBack(benchmark::State& state, DynamicArray<T>* array)
{
    for (auto i = 0; i < state.range(0); i++) {
        array->add(i);
    }

    const T value = 1;
    for (auto _ : state) {
        array->add(value);
    }
    state.SetComplexityN(state.range(0));
}

template <typename T>
static void removeFront(benchmark::State& state, DynamicArray<T>* array)
{
    // массив наполняется первоначальными данными, которые будут удаляться
    for (auto i = 0; i < state.range(0); i++) {
        array->add(i);
    }

    const T value = 1;
    for (auto _ : state) {
        // удалённый элемент компенсируется
        state.PauseTiming();
        array->add(value, 0);
        state.ResumeTiming();

        array->remove(0);
    }
    state.SetComplexityN(state.range(0));
}

template <typename T>
static void removeBack(benchmark::State& state, DynamicArray<T>* array)
{

    // массив наполняется первоначальными данными, которые будут удаляться
    for (auto i = 0; i < state.range(0) - 1; i++) {
        array->add(i);
    }

    const T value = 1;
    for (auto _ : state) {
        // удалённый элемент компенсируется
        state.PauseTiming();
        array->add(value);
        state.ResumeTiming();

        array->remove(array->size() - 1);
    }
    state.SetComplexityN(state.range(0));
}

template <typename T>
static void get(benchmark::State& state, DynamicArray<T>* array)
{
    for (auto i = 0; i < state.range(0); i++) {
        array->add(i);
    }
    T val;

    // читаем из середины массива
    auto ix = array->size() / 2;
    for (auto _ : state) {
        benchmark::DoNotOptimize(array->get(ix));
    }
    state.SetComplexityN(state.range(0));
}

// add front

template <typename T>
static void BM_DynamicArray_AddFront_Simple(benchmark::State& state)
{
    T array;
    addFront<int>(state, &array);
}

template <typename T>
static void BM_DynamicArray_AddFront_Parametrized(benchmark::State& state)
{
    T array(static_cast<size_t>(state.range(1)));
    addFront<int>(state, &array);
}

// add back

template <typename T>
static void BM_DynamicArray_AddBack_Simple(benchmark::State& state)
{
    T array;
    addBack<int>(state, &array);
}

template <typename T>
static void BM_DynamicArray_AddBack_Parametrized(benchmark::State& state)
{
    T array(static_cast<size_t>(state.range(1)));
    addBack<int>(state, &array);
}

// remove front

template <typename T>
static void BM_DynamicArray_RemoveFront_Simple(benchmark::State& state)
{
    T array;
    removeFront<int>(state, &array);
}

template <typename T>
static void BM_DynamicArray_RemoveFront_Parametrized(benchmark::State& state)
{
    T array(static_cast<size_t>(state.range(1)));
    removeFront<int>(state, &array);
}

// remove back

template <typename T>
static void BM_DynamicArray_RemoveBack_Simple(benchmark::State& state)
{
    T array;
    removeBack<int>(state, &array);
}

template <typename T>
static void BM_DynamicArray_RemoveBack_Parametrized(benchmark::State& state)
{
    T array(static_cast<size_t>(state.range(1)));
    removeBack<int>(state, &array);
}

// get

template <typename T>
static void BM_DynamicArray_Get_Simple(benchmark::State& state)
{
    T array;
    get<int>(state, &array);
}

template <typename T>
static void BM_DynamicArray_Get_Parametrized(benchmark::State& state)
{
    T array(static_cast<size_t>(state.range(1)));
    get<int>(state, &array);
}

// benchmark options

std::vector<int> iteration_values = {2 << 0, 2 << 3, 2 << 7, 2 << 11, 2 << 15, 2 << 17};
std::vector<int> parameter_values = {2 << 0, 2 << 15};

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

BENCHMARK_TEMPLATE(BM_DynamicArray_AddFront_Simple, SingleArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_AddFront_Parametrized, VectorArray<int>)->Apply(TwoPositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_AddFront_Simple, FactorArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_AddFront_Simple, StdVectorArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_AddFront_Parametrized, MatrixArray<int>)->Apply(TwoPositionArgs);

BENCHMARK_TEMPLATE(BM_DynamicArray_AddBack_Simple, SingleArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_AddBack_Parametrized, VectorArray<int>)->Apply(TwoPositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_AddBack_Simple, FactorArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_AddBack_Simple, StdVectorArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_AddBack_Parametrized, MatrixArray<int>)->Apply(TwoPositionArgs);

BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveFront_Simple, SingleArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveFront_Parametrized, VectorArray<int>)->Apply(TwoPositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveFront_Simple, FactorArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveFront_Simple, StdVectorArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveFront_Parametrized, MatrixArray<int>)->Apply(TwoPositionArgs);

BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveBack_Simple, SingleArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveBack_Parametrized, VectorArray<int>)->Apply(TwoPositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveBack_Simple, FactorArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveBack_Simple, StdVectorArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_RemoveBack_Parametrized, MatrixArray<int>)->Apply(TwoPositionArgs);

BENCHMARK_TEMPLATE(BM_DynamicArray_Get_Simple, SingleArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_Get_Parametrized, VectorArray<int>)->Apply(TwoPositionArgs);
BENCHMARK_TEMPLATE(BM_DynamicArray_Get_Simple, FactorArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_Get_Simple, StdVectorArray<int>)->Apply(OnePositionArgs)->Complexity();
BENCHMARK_TEMPLATE(BM_DynamicArray_Get_Parametrized, MatrixArray<int>)->Apply(TwoPositionArgs);