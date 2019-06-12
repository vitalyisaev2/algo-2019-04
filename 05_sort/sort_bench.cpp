#include "insertion_sort.hpp"
#include "shell_sort.hpp"
#include "sequence_generator.hpp"
#include <benchmark/benchmark.h>

SequenceGenerator<long> generator;
ShellSortFactory shellSortFactory;

static void sort_array(sort_func<long> f, SequenceGenerator<long>::Kind kind, benchmark::State& state)
{
    auto n = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        auto seq = generator.GetSequence(n, kind);
        state.ResumeTiming();
        f(seq);
    }
    state.SetComplexityN(state.range(0));
}

template <typename T>
void BM_05_SortShuffled100Percent(benchmark::State& state)
{
    sort_array(T().f, SequenceGenerator<long>::Kind::Shuffled100Percent, state);
}

template <typename T>
void BM_05_SortShuffled10Percent(benchmark::State& state)
{
    sort_array(T().f, SequenceGenerator<long>::Kind::Shuffled10Percent, state);
}

template <typename T>
void BM_05_SortShuffled5Items(benchmark::State& state)
{
    sort_array(T().f, SequenceGenerator<long>::Kind::Shuffled5Items, state);
}

template <typename T>
class InsertionSort
{
  public:
    sort_func<T> f = insertion_sort<T>;
};

template <typename T>
class ShellSortDefaultSequence
{
  public:
    sort_func<T> f = shellSortFactory.Get<T>(ShellSortFactory::Sequence::Default);
};

BENCHMARK_TEMPLATE(BM_05_SortShuffled100Percent, InsertionSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 15)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled10Percent, InsertionSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 15)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled5Items, InsertionSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 15)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled100Percent, ShellSortDefaultSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 15)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled10Percent, ShellSortDefaultSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 15)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled5Items, ShellSortDefaultSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 15)->Complexity();