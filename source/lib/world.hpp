#ifndef WORLD_OF_CUBE_WORLD_HPP
#define WORLD_OF_CUBE_WORLD_HPP

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <string_view>
#include <vector>

#include <omp.h>

#include "PerlinNoise.hpp"
#include "raylib.h"

// Cube lib
#include "block.hpp"
#include "chunk.hpp"
#include "generatorv1.hpp"
#include "generatorv2.hpp"
#include "world_model.hpp"
#include "game_class.hpp"
#include "game_context.hpp"

class world : public game_class
{
    public:
        world(game_context& game_context_ref);

        ~world();

        void generate_world();
        void generate_world_models();

        void generate_chunk(const int32_t, const int32_t, const int32_t, bool);
        std::unique_ptr<chunk> generate_chunk_models(std::unique_ptr<chunk>);
        bool is_chunk_exist(const int32_t, const int32_t, const int32_t);

        void clear();

        void update() override;
        void draw2d() override;
        void draw3d() override;

        int32_t world_chunk_size_x = 4;
        int32_t world_chunk_size_y = 2;
        int32_t world_chunk_size_z = 4;

        int32_t world_chunk_start_x = 0;
        int32_t world_chunk_start_y = 0;
        int32_t world_chunk_start_z = 0;

        siv::PerlinNoise::seed_type seed = 2510586073u;

        generatorv1 genv1 = generatorv1(this->seed);
        generatorv2 genv2 = generatorv2(this->seed);

        world_model world_md = world_model();

        std::vector<std::unique_ptr<chunk>> chunks;

        bool display_debug_menu = true;
        int32_t render_distance = 2;

        game_context& _game_context_ref;
};

#endif  // WORLD_OF_CUBE_WORLD_HPP