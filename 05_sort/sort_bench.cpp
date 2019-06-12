#include "insertion_sort.hpp"
#include "sequence_generator.hpp"
#include "shell_sort.hpp"
#include <benchmark/benchmark.h>

utils::SequenceGenerator<long> generator;
algo::ShellSortFactory         shellSortFactory;

template <typename Sorter>
static void sortArray(utils::SequenceGenerator<long>::Kind kind, benchmark::State& state)
{
    Sorter s;
    auto   n = static_cast<size_t>(state.range(0));
    for (auto _ : state) {
        state.PauseTiming();
        auto f   = s.f;
        auto seq = generator.GetSequence(n, kind);
        state.ResumeTiming();
        f(seq);
    }
    state.SetComplexityN(state.range(0));
}

template <typename T>
void BM_05_SortShuffled100Percent(benchmark::State& state)
{
    sortArray<T>(utils::SequenceGenerator<long>::Kind::Shuffled100Percent, state);
}

template <typename T>
void BM_05_SortShuffled10Percent(benchmark::State& state)
{
    sortArray<T>(utils::SequenceGenerator<long>::Kind::Shuffled10Percent, state);
}

template <typename T>
void BM_05_SortShuffled5Items(benchmark::State& state)
{
    sortArray<T>(utils::SequenceGenerator<long>::Kind::Shuffled5Items, state);
}

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

BENCHMARK_TEMPLATE(BM_05_SortShuffled100Percent, InsertionSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled10Percent, InsertionSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled5Items, InsertionSort<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled100Percent, ShellSortShellSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled10Percent, ShellSortShellSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled5Items, ShellSortShellSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled100Percent, ShellSortSedgewickSequence<long>)
    ->RangeMultiplier(2)
    ->Range(1 << 1, 1 << 16)
    ->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled10Percent, ShellSortSedgewickSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled5Items, ShellSortSedgewickSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled100Percent, ShellSortCiuraSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled10Percent, ShellSortCiuraSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();
BENCHMARK_TEMPLATE(BM_05_SortShuffled5Items, ShellSortCiuraSequence<long>)->RangeMultiplier(2)->Range(1 << 1, 1 << 16)->Complexity();