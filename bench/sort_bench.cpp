#include "common_sort.hpp"
#include "counting_sort.hpp"
#include "heap_sort.hpp"
#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "radix_sort.hpp"
#include "sequence_generator.hpp"
#include "shell_sort.hpp"
#include <benchmark/benchmark.h>

utils::SequenceGenerator<long> generator;
algo::ShellSortFactory         shellSortFactory;

// sortArrayProportionalDistribution - сортировка массива, в котором диапазон данных пропорционален длине массива
template <typename Sorter>
static void sortArrayProportionalDistribution(utils::SequenceGenerator<long>::Kind kind, benchmark::State& state)
{
    Sorter s;
    auto   n = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        auto f   = s.f;
        auto seq = generator.GetSequence(n, static_cast<long>(n), kind);
        state.ResumeTiming();
        f(seq);
    }
    state.SetComplexityN(state.range(0));
}

template <typename T>
void BM_SortShuffled100Percent_PD(benchmark::State& state)
{
    sortArrayProportionalDistribution<T>(utils::SequenceGenerator<long>::Kind::Shuffled100Percent, state);
}

template <typename T>
void BM_SortShuffled10Percent_PD(benchmark::State& state)
{
    sortArrayProportionalDistribution<T>(utils::SequenceGenerator<long>::Kind::Shuffled10Percent, state);
}

template <typename T>
void BM_SortShuffled5Items_PD(benchmark::State& state)
{
    sortArrayProportionalDistribution<T>(utils::SequenceGenerator<long>::Kind::Shuffled5Items, state);
}

// классы-контейнеры для функций сортировки

template <typename T>
class InsertionSort
{
  public:
    algo::SortFunc<T> f = algo::InsertionSort<T>;
};

template <typename T>
class ShellSortShellSequence
{
  public:
    algo::SortFunc<T> f = shellSortFactory.Get<T>(algo::ShellSortFactory::Sequence::Shell);
};

template <typename T>
class ShellSortSedgewickSequence
{
  public:
    algo::SortFunc<T> f = shellSortFactory.Get<T>(algo::ShellSortFactory::Sequence::Sedgewick);
};

template <typename T>
class ShellSortCiuraSequence
{
  public:
    algo::SortFunc<T> f = shellSortFactory.Get<T>(algo::ShellSortFactory::Sequence::Ciura);
};

template <typename T>
class HeapSort
{
  public:
    algo::SortFunc<T> f = algo::HeapSort<T>;
};

template <typename T>
class MergeSort
{
  public:
    algo::SortFunc<T> f = algo::MergeSort<T>;
};

template <typename T>
class QuickSort
{
  public:
    algo::SortFunc<T> f = algo::QuickSort<T>;
};

template <typename T>
class CountingSort
{
  public:
    algo::SortFunc<T> f = algo::CountingSort<T>;
};

template <typename T>
class RadixSort
{
  public:
    algo::SortFunc<T> f = algo::RadixSort<T>;
};

// Hw05
BENCHMARK_TEMPLATE(BM_SortShuffled100Percent_PD, InsertionSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled10Percent_PD, InsertionSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled5Items_PD, InsertionSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled100Percent_PD, ShellSortShellSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled10Percent_PD, ShellSortShellSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled5Items_PD, ShellSortShellSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled100Percent_PD, ShellSortSedgewickSequence<long>)
    ->RangeMultiplier(2)
    ->Range(1 << 1, 1 << 16)
    ->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled10Percent_PD, ShellSortSedgewickSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled5Items_PD, ShellSortSedgewickSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled100Percent_PD, ShellSortCiuraSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled10Percent_PD, ShellSortCiuraSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled5Items_PD, ShellSortCiuraSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();

// Hw06
BENCHMARK_TEMPLATE(BM_SortShuffled100Percent_PD, HeapSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled10Percent_PD, HeapSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled5Items_PD, HeapSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();

// Hw07
BENCHMARK_TEMPLATE(BM_SortShuffled100Percent_PD, MergeSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled10Percent_PD, MergeSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled5Items_PD, MergeSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled100Percent_PD, QuickSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled10Percent_PD, QuickSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled5Items_PD, QuickSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();

// HW08
BENCHMARK_TEMPLATE(BM_SortShuffled100Percent_PD, CountingSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled10Percent_PD, CountingSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled5Items_PD, CountingSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled100Percent_PD, RadixSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled10Percent_PD, RadixSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_SortShuffled5Items_PD, RadixSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();