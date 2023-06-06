#include "generator.hpp"

#include <benchmark/benchmark.h>

#include "PerlinNoise.hpp"

static void generate_3d_word(benchmark::State& state)
{
    auto size = state.range(0);
    siv::PerlinNoise::seed_type seed = 2510586073u;

    generator gen = generator(seed);

    for (auto _ : state) {
        std::vector<std::unique_ptr<chunk>> chunks = std::move(gen.generate_chunks(0, 0, 0, size, 1, size, true));
        benchmark::DoNotOptimize(chunks);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations() * size * size);
    state.SetBytesProcessed(state.iterations() * size * size * sizeof(chunk));
}
BENCHMARK(generate_3d_word)->Name("generate_3d_word")->RangeMultiplier(2)->Range(1, 8)->ThreadRange(1, 1);

static void generate_3d_chunk(benchmark::State& state)
{
    auto size = state.range(0);
    siv::PerlinNoise::seed_type seed = 2510586073u;

    generator gen = generator(seed);

    for (auto _ : state) {
        std::unique_ptr<chunk> _chunk = std::move(gen.generate_chunk(0, 0, 0, true));
        benchmark::DoNotOptimize(_chunk);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations());
    state.SetBytesProcessed(state.iterations() * sizeof(chunk));
}
BENCHMARK(generate_3d_chunk)->Name("generate_3d_chunk")->RangeMultiplier(2)->Range(1, 1)->ThreadRange(1, 1);

static void generate_2d_word(benchmark::State& state)
{
    auto size = state.range(0);
    siv::PerlinNoise::seed_type seed = 2510586073u;

    generator gen = generator(seed);

    for (auto _ : state) {
        std::vector<std::unique_ptr<chunk>> chunks = std::move(gen.generate_chunks(0, 0, 0, size, 1, size, false));
        benchmark::DoNotOptimize(chunks);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations() * size * size);
    state.SetBytesProcessed(state.iterations() * size * size * sizeof(chunk));
}
BENCHMARK(generate_2d_word)->Name("generate_2d_word")->RangeMultiplier(2)->Range(1, 8)->ThreadRange(1, 1);

static void generate_2d_chunk(benchmark::State& state)
{
    auto size = state.range(0);
    siv::PerlinNoise::seed_type seed = 2510586073u;

    generator gen = generator(seed);

    for (auto _ : state) {
        std::unique_ptr<chunk> _chunk = std::move(gen.generate_chunk(0, 0, 0, false));
        benchmark::DoNotOptimize(_chunk);
        benchmark::ClobberMemory();
    }
    state.SetItemsProcessed(state.iterations());
    state.SetBytesProcessed(state.iterations() * sizeof(chunk));
}
BENCHMARK(generate_2d_chunk)->Name("generate_2d_chunk")->RangeMultiplier(2)->Range(1, 1)->ThreadRange(1, 1);
