#include <benchmark/benchmark.h>

#ifndef FASTNOISE_PERLINNOISE_HPP_INCLUDED
#define FASTNOISE_PERLINNOISE_HPP_INCLUDED
#ifdef __GNUC__
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#include "FastNoise/FastNoise.h"
#endif

/*
static void generate_3d_word(benchmark::State &state) {
  auto size = state.range(0);
  siv::PerlinNoise::seed_type seed = 2510586073u;

  generatorv1 gen = generatorv1(seed);

  for (auto _ : state) {
    std::vector<std::unique_ptr<Chunk>> chunks = std::move(gen.generateChunks(0, 0, 0, size, 1, size, true));
    benchmark::DoNotOptimize(chunks);
    benchmark::ClobberMemory();
  }
  state.SetItemsProcessed(state.iterations() * size * size);
  state.SetBytesProcessed(state.iterations() * size * size * sizeof(Chunk));
}
BENCHMARK(generate_3d_word)->Name("generate_3d_word")->RangeMultiplier(2)->Range(1, 8)->ThreadRange(1, 1);

static void generate_3d_chunk(benchmark::State &state) {
  auto size = state.range(0);
  siv::PerlinNoise::seed_type seed = 2510586073u;

  generatorv1 gen = generatorv1(seed);

  for (auto _ : state) {
    std::unique_ptr<Chunk> _chunk = std::move(gen.generateChunk(0, 0, 0, true));
    benchmark::DoNotOptimize(_chunk);
    benchmark::ClobberMemory();
  }
  state.SetItemsProcessed(state.iterations());
  state.SetBytesProcessed(state.iterations() * sizeof(Chunk));
}
BENCHMARK(generate_3d_chunk)->Name("generate_3d_chunk")->RangeMultiplier(2)->Range(1, 1)->ThreadRange(1, 1);

static void generate_2d_word(benchmark::State &state) {
  auto size = state.range(0);
  siv::PerlinNoise::seed_type seed = 2510586073u;

  generatorv1 gen = generatorv1(seed);

  for (auto _ : state) {
    std::vector<std::unique_ptr<Chunk>> chunks = std::move(gen.generateChunks(0, 0, 0, size, 1, size, false));
    benchmark::DoNotOptimize(chunks);
    benchmark::ClobberMemory();
  }
  state.SetItemsProcessed(state.iterations() * size * size);
  state.SetBytesProcessed(state.iterations() * size * size * sizeof(Chunk));
}
BENCHMARK(generate_2d_word)->Name("generate_2d_word")->RangeMultiplier(2)->Range(1, 8)->ThreadRange(1, 1);

static void generate_2d_chunk(benchmark::State &state) {
  auto size = state.range(0);
  siv::PerlinNoise::seed_type seed = 2510586073u;

  generatorv1 gen = generatorv1(seed);

  for (auto _ : state) {
    std::unique_ptr<Chunk> _chunk = std::move(gen.generateChunk(0, 0, 0, false));
    benchmark::DoNotOptimize(_chunk);
    benchmark::ClobberMemory();
  }
  state.SetItemsProcessed(state.iterations());
  state.SetBytesProcessed(state.iterations() * sizeof(Chunk));
}
BENCHMARK(generate_2d_chunk)->Name("generate_2d_chunk")->RangeMultiplier(2)->Range(1, 1)->ThreadRange(1, 1);
*/

#include <string>
#include <iostream>

#include <benchmark/benchmark.h>

static void DoSetup(const benchmark::State& state) {
}

static void DoTeardown(const benchmark::State& state) {
}

template<typename T>
static void BasicBench(benchmark::State& state) {
  const auto range = state.range(0);
  std::string str;
  benchmark::DoNotOptimize(str);

  for (auto _ : state) {
    str = std::to_string(range);
    benchmark::ClobberMemory();
    //state.PauseTiming();
    //state.SkipWithError("No path found");
    //state.ResumeTiming();
  }
  // state.counters["range"] = range;
  state.SetItemsProcessed(state.iterations() * range * range);
  state.SetBytesProcessed(state.iterations() * range * range * sizeof(uint64_t));
}
BENCHMARK(BasicBench<uint64_t>)
    ->Name("BasicBench")
    ->RangeMultiplier(4)
    ->Range(16, 256)
    ->ThreadRange(1, 1)
    ->Unit(benchmark::kNanosecond)
    ->Setup(DoSetup)
    ->Teardown(DoTeardown)
    ->MeasureProcessCPUTime()
    ->UseRealTime();

int main(int argc, char** argv) {
   ::benchmark::Initialize(&argc, argv);
   ::benchmark::RunSpecifiedBenchmarks();
}