#ifndef WORLD_OF_CUBE_CHUNK_HPP
#define WORLD_OF_CUBE_CHUNK_HPP

// Cube lib
#include "block.hpp"
#include "math.hpp"
#include "raylib.h"

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

        [[nodiscard]] inline std::vector<block>& get_blocks() { return blocks; }

        [[nodiscard]] inline block& get_block(const int x, const int y, const int z)
        {
            return blocks[math::convert_to_1d(x, y, z, chunk_size_x, chunk_size_y, chunk_size_z)];
        }

        void set_blocks(std::vector<block>& blocks) { this->blocks = std::move(blocks); }

        [[nodiscard]] std::vector<block>::size_type size() const { return blocks.size(); }

        [[nodiscard]] Vector3i chunk_size() const { return {chunk_size_x, chunk_size_y, chunk_size_z}; }

        [[nodiscard]] Vector3i get_position() const { return {chunk_x, chunk_y, chunk_z}; }

        void set_chuck_pos(const int x, const int y, const int z)
        {
            chunk_x = x;
            chunk_y = y;
            chunk_z = z;
        }

        static constexpr int chunk_size_x = 16;
        static constexpr int chunk_size_y = 64;
        static constexpr int chunk_size_z = 16;

    protected:
        std::vector<block> blocks;

        // Chunk coordinates
        int chunk_x = 0;
        int chunk_y = 0;
        int chunk_z = 0;
};

#endif  // WORLD_OF_CUBE_CHUNK_HPP