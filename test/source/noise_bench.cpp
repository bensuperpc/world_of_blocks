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
#include "PerlinNoise.hpp"
#endif

static void perlin_noise_octave3d_01(benchmark::State &state) {
  auto size = state.range(0);

  auto size_x = size;
  auto size_y = size;
  auto size_z = size;

  int32_t octaves = 4;
  double persistence = 0.5;
  double lacunarity = 255.0f;

  siv::PerlinNoise::seed_type seed = 264739307;
  siv::PerlinNoise perlin{seed};

  for (auto _ : state) {
    for (int64_t x = 0; x < size_x; x++) {
      for (int64_t y = 0; y < size_y; y++) {
        for (int64_t z = 0; z < size_z; z++) {
          benchmark::DoNotOptimize(
              perlin.octave3D_01(static_cast<double>(x) / 256.0, static_cast<double>(y) / 256.0, static_cast<double>(z) / 256.0, octaves, persistence) *
              lacunarity);
          benchmark::ClobberMemory();
        }
      }
    }
  }
  state.SetItemsProcessed(state.iterations() * size_x * size_y * size_z);
  state.SetBytesProcessed(state.iterations() * size_x * size_y * size_z * sizeof(double));
}
BENCHMARK(perlin_noise_octave3d_01)->Name("perlin_noise_octave3d_01")->RangeMultiplier(2)->Range(1, 32)->ThreadRange(1, 1);

static void fastnoise2_octave3d(benchmark::State &state) {
  auto size = state.range(0);

  auto size_x = size;
  auto size_y = size;
  auto size_z = size;

  int32_t octaves = 4;
  double persistence = 0.5;
  double lacunarity = 255.0f;

  int seed = 264739307;

  std::vector<float> noise_output(size_x * size_y * size_z);

  auto fnSimplex = FastNoise::New<FastNoise::Simplex>();
  auto fnFractal = FastNoise::New<FastNoise::FractalFBm>();

  // double lacunarity = 255.0f;
  fnFractal->SetSource(fnSimplex);
  fnFractal->SetOctaveCount(octaves);
  // fnFractal->SetGain(0.8f);
  fnFractal->SetLacunarity(lacunarity);

  for (auto _ : state) {
    benchmark::DoNotOptimize(fnFractal->GenUniformGrid3D(noise_output.data(), 0, 0, 0, size_x, size_y, size_z, 0.2f, seed));
    benchmark::ClobberMemory();
  }
  state.SetItemsProcessed(state.iterations() * size_x * size_y * size_z);
  state.SetBytesProcessed(state.iterations() * size_x * size_y * size_z * sizeof(double));
}
BENCHMARK(fastnoise2_octave3d)->Name("fastnoise2_octave3d")->RangeMultiplier(2)->Range(4, 64)->ThreadRange(1, 1);