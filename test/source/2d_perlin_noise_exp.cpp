#include <array>    // std::array
#include <chrono>   // std::chrono::system_clock
#include <iostream> // std::cout, std::endl
#include <map>      // std::map
#include <memory>   // std::unique_ptr
#include <random>   // std::random_device, std::mt19937, std::uniform_int_distribution
#include <vector>   // std::vector

#include "generatorv2.hpp"

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
extern "C" {
#include "src/raygui.h"
}

#include "raylib-cpp.hpp"

auto main() -> int {
  const int screenWidth = 1920;
  const int screenHeight = 1080;

  const uint32_t targetFPS = 240;

  const uint32_t ImageUpdatePerSecond = 10;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);

  raylib::Window window(screenWidth, screenHeight, "Perlin Noise by Bensuperpc");

  SetTargetFPS(targetFPS);

  raylib::Image gridImage(screenWidth, screenHeight, RAYWHITE);

  Color *pixels = gridImage.LoadColors();

  raylib::Texture gridTexture(gridImage);

  float lacunarity = 0.5f;
  uint32_t octaves = 6;
  float gain = 3.5f;
  float frequency = 0.4f;
  float weighted_strength = 0.0f;
  uint32_t multiplier = 128;

  generatorv2 generator_2(2510586073u);
  generator_2.set_lacunarity(lacunarity);
  generator_2.set_octaves(octaves);
  generator_2.set_gain(gain);
  generator_2.set_frequency(frequency);
  generator_2.set_weighted_strength(0.0f);
  generator_2.set_multiplier(multiplier);

  bool forceSquaredChecked = false;

  std::vector<uint32_t> blocks;

  blocks = generator_2.generate_2d_heightmap(0, 0, 0, screenWidth, 0, screenHeight);

  uint64_t framesCounter = 0;

  while (!WindowShouldClose()) {
    framesCounter++;
    if (IsKeyPressed(KEY_S)) {
      const std::string filename = "screenshot_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + ".png";
      auto img = raylib::Image(pixels, screenWidth, screenHeight);
      img.FlipVertical();
      img.Export(filename);
      img.FlipVertical();
      pixels = img.LoadColors();
    }
    if (IsKeyPressed(KEY_R)) {
      std::cout << "New seed: " << generator_2.randomize_seed() << std::endl;
    }

    if (framesCounter % (targetFPS / ImageUpdatePerSecond) == 0) {
      generator_2.set_lacunarity(lacunarity);
      generator_2.set_octaves(octaves);
      generator_2.set_gain(gain);
      generator_2.set_frequency(frequency);
      generator_2.set_weighted_strength(weighted_strength);
      generator_2.set_multiplier(multiplier);

      blocks = generator_2.generate_2d_heightmap(0, 0, 0, screenWidth, 0, screenHeight);
      for (uint64_t x = 0; x < screenWidth; x++) {
        for (uint64_t y = 0; y < screenHeight; y++) {
          const uint64_t index = x + y * screenWidth;
          const uint8_t value = static_cast<uint8_t>(blocks[index]);
          pixels[index] = {value, value, value, 255};
        }
      }

      // Update texture
      gridTexture.Update(pixels);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(gridTexture, 0, 0, WHITE);

    // display FPS
    DrawRectangle(screenWidth - 90, 10, 80, 20, Fade(SKYBLUE, 0.95f));
    DrawText(TextFormat("FPS: %02d", GetFPS()), screenWidth - 80, 15, 15, DARKGRAY);

    DrawRectangle(0, 0, 275, 200, Fade(SKYBLUE, 0.95f));
    DrawRectangleLines(0, 0, 275, 200, BLUE);
    lacunarity = GuiSlider((Rectangle){70, 10, 165, 20}, "Lacunarity", TextFormat("%2.3f", lacunarity), lacunarity, -0.0f, 5.0f);
    octaves = GuiSlider((Rectangle){70, 40, 165, 20}, "Octaves", TextFormat("%d", octaves), octaves, 1, 12);
    gain = GuiSlider((Rectangle){70, 70, 165, 20}, "Gain", TextFormat("%2.3f", gain), gain, -0.0f, 16.0f);
    frequency = GuiSlider((Rectangle){70, 100, 165, 20}, "Frequency", TextFormat("%2.3f", frequency), frequency, -0.0f, 10.0f);
    weighted_strength = GuiSlider((Rectangle){70, 130, 165, 20}, "Weight", TextFormat("%2.3f", weighted_strength), weighted_strength, -5.0f, 5.0f);
    multiplier = GuiSlider((Rectangle){70, 160, 165, 20}, "Multiplier", TextFormat("%d", multiplier), multiplier, 1, 512);

    EndDrawing();
  }
  gridImage.UnloadColors(pixels);

  return 0;
}