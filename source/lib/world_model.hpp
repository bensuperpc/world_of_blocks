#ifndef WORLD_OF_CUBE_WORLD_MODEL_HPP
#define WORLD_OF_CUBE_WORLD_MODEL_HPP
#include <vector>

#include <omp.h>

#include "raylib.h"
#include "raymath.h"

// Cube lib
#include "block.hpp"
#include "chunk.hpp"
#include "math.hpp"

class world_model
{
    public:
        world_model() {}

        ~world_model() {}

        static constexpr size_t south_face = 0;
        static constexpr size_t north_face = 1;
        static constexpr size_t west_face = 2;
        static constexpr size_t east_face = 3;
        static constexpr size_t up_face = 4;
        static constexpr size_t down_face = 5;

        inline void add_vertex(
            Mesh& mesh, size_t& triangle_index, size_t& vert_index, Vector3& vertex, Vector3 offset, Vector3 normal, Vector2 texcoords);

        void add_cube(Mesh& mesh, size_t& triangle_index, size_t& vert_index, Vector3&& position, bool faces[6], int block);

        std::vector<Model> generate_world_models(std::vector<chunk>& chunk);
        Model generate_chunk_model(chunk& chunks);

        inline bool block_is_solid(int x, int y, int z, chunk& _chunk);

        inline int count_neighbours(int x, int y, int z, chunk& _chunk);

        inline int count_border(int x, int y, int z, chunk& _chunk);

        int face_count(chunk& _chunk);

        Mesh chunk_mesh(chunk& chunk);
};

#endif  // WORLD_OF_CUBE_WORLD_HPP