#include <benchmark/benchmark.h>

static void int_radius(benchmark::State &state) {
  // Code inside this loop is measured repeatedly
  auto size = state.range(0);
  for (auto _ : state) {
    uint64_t radius{65};
    benchmark::DoNotOptimize(radius);
    benchmark::ClobberMemory();
  }
  state.SetItemsProcessed(state.iterations());
  state.SetBytesProcessed(state.iterations() * state.range(0) * sizeof(uint64_t));
}
BENCHMARK(int_radius)->Name("int_radius")->RangeMultiplier(16)->Range(1, 1048576);
