#ifndef CUBE_CHUNK_HPP
#define CUBE_CHUNK_HPP

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
// Raylib
#include "raylib-cpp.hpp"
#include "raylib.h"
#include "raymath.h"

// Cube lib
#include "block.hpp"

class chunk
{
    public:
        chunk() {}
        chunk(std::vector<block> blocks, int chunk_x, int chunk_y, int chunk_z)
            : blocks(std::move(blocks))
            , chunk_x(chunk_x)
            , chunk_y(chunk_y)
            , chunk_z(chunk_z)
        {
        }

        ~chunk() {}

        [[nodiscard]] raylib::Vector3 get_position() const { return {chunk_x, chunk_y, chunk_z}; }
        [[nodiscard]] std::vector<block>& get_blocks() { return blocks; }
        void set_blocks(std::vector<block>& blocks) { this->blocks = std::move(blocks); }


        /*
        [[nodiscard]] raylib::Vector3 get_real_position() const
        {
            return {chunk_x * chunk_size_x * block::size_x,
                    chunk_y * chunk_size_y * block::size_y,
                    chunk_z * chunk_size_z * block::size_z};
        }


        void draw_box() const
        {
            raylib::Vector3 pos = get_real_position();
            pos.x += chunk_size_x - block::size_x / 2;
            pos.y += chunk_size_y - block::size_y / 2;
            pos.z += chunk_size_z - block::size_z / 2;
            raylib::Vector3 size = {
                chunk_size_x * block::size_x, chunk_size_y * block::size_y, chunk_size_z * block::size_z};
            raylib::Color color = raylib::Color::Green();
            DrawCubeWiresV(pos, size, color);
        }
        
        //[[nodiscard]] block& get_block(int index) { return blocks[index]; }
        // void set_block(int chuck_index, block &b) { blocks[chuck_index] = b; }

        //[[nodiscard]] block& get_block(int x, int y, int z) { return blocks[z * chunk_size_x + y * chunk_size_x *
        // chunk_size_z + x]; }
        //[[nodiscard]] block& get_block(int x, int y, int z) { return blocks[z * chunk_x + y * chunk_x * chunk_z + x];
        //}

        [[nodiscard]] raylib::Vector3 get_size() const
        {
            return {chunk_size_x * block::size_x, chunk_size_y * block::size_y, chunk_size_z * block::size_z};
        }
        */

        [[nodiscard]] std::vector<block>::size_type size() const { return blocks.size(); }

        static constexpr int chunk_size_x = 16;
        static constexpr int chunk_size_y = 64;
        static constexpr int chunk_size_z = 16;

        // TODO: Remove this
        static constexpr std::vector<block>::size_type chunk_size = chunk_size_x * chunk_size_y * chunk_size_z;

        void set_chuck_pos(const int x, const int y, const int z)
        {
            chunk_x = x;
            chunk_y = y;
            chunk_z = z;
        }

    private:
        std::vector<block> blocks = std::vector<block>(chunk_size, block());

        // Chunk coordinates
        int chunk_x = 0;
        int chunk_y = 0;
        int chunk_z = 0;
};

#endif  // CUBE_CHUNK_HPP