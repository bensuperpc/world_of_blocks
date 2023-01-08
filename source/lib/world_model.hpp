#ifndef WORLD_OF_CUBE_WORLD_MODEL_HPP
#define WORLD_OF_CUBE_WORLD_MODEL_HPP

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
#include <rlgl.h>

#include "raylib-cpp.hpp"
#include "raylib.h"
#include "raymath.h"
// memcpy
#include <stdio.h>
#include <string.h>

// Cube lib
#include "block.hpp"
#include "chunk.hpp"
#include "math.hpp"

class world_model
{
    public:
        world_model() {}

        ~world_model() {}

        inline void add_vertex(Mesh& mesh,
                               size_t& triangle_index,
                               size_t& vert_index,
                               Vector3& vertex,
                               Vector3 offset,
                               Vector3 normal,
                               Vector2 texcoords)
        {
            size_t index = triangle_index * 12 + vert_index * 3;

            index = triangle_index * 6 + vert_index * 2;
            mesh.texcoords[index] = texcoords.x;
            mesh.texcoords[index + 1] = texcoords.y;

            index = triangle_index * 9 + vert_index * 3;
            mesh.normals[index] = normal.x;
            mesh.normals[index + 1] = normal.y;
            mesh.normals[index + 2] = normal.z;

            index = triangle_index * 9 + vert_index * 3;
            mesh.vertices[index] = vertex.x + offset.x;
            mesh.vertices[index + 1] = vertex.y + offset.y;
            mesh.vertices[index + 2] = vertex.z + offset.z;

            vert_index++;
            if (vert_index > 2) {
                triangle_index++;
                vert_index = 0;
            }
        }

        void AddCube(
            Mesh& mesh, size_t& triangle_index, size_t& vert_index, Vector3&& position, bool faces[6], int block)
        {
            Rectangle texcoords_rect = Rectangle {0.25f, 0, 0.5f, 1};
            // z-
            if (faces[1]) {
                Vector3 normal = Vector3 {0, 0, -1};

                add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

                add_vertex(
                    mesh, triangle_index, vert_index, position, {1, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.height});

                add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

                // Issue with this triangle
                add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.width});

                add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 0}, normal, {texcoords_rect.x, texcoords_rect.height});

                // Seems to be fixed here
                add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 0}, normal, {texcoords_rect.y, texcoords_rect.width});
            }

            // z+
            if (faces[0]) {
                Vector3 normal = Vector3 {0, 0, 1};

                add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.y});

                add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 1}, normal, {texcoords_rect.width, texcoords_rect.y});

                add_vertex(
                    mesh, triangle_index, vert_index, position, {1, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

                add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.y});

                add_vertex(
                    mesh, triangle_index, vert_index, position, {1, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

                add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 1}, normal, {texcoords_rect.x, texcoords_rect.height});
            }

            // x+
            if (faces[2]) {
                Vector3 normal = Vector3 {1, 0, 0};

                add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.height});

                add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

                add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

                add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.height});

                add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

                add_vertex(
                    mesh, triangle_index, vert_index, position, {1, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});
            }

            // x-
            if (faces[3]) {
                Vector3 normal = Vector3 {-1, 0, 0};

                add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.height});

                add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

                add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

                add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.height});

                add_vertex(
                    mesh, triangle_index, vert_index, position, {0, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

                add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.y});
            }

            if (faces[4]) {
                Vector3 normal = Vector3 {0, 1, 0};

                add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

                add_vertex(
                    mesh, triangle_index, vert_index, position, {1, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

                add_vertex(mesh, triangle_index, vert_index, position, {1, 1, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

                add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

                add_vertex(mesh, triangle_index, vert_index, position, {0, 1, 1}, normal, {texcoords_rect.x, texcoords_rect.height});

                add_vertex(
                    mesh, triangle_index, vert_index, position, {1, 1, 1}, normal, {texcoords_rect.width, texcoords_rect.height});
            }

            if (faces[5]) {
                Vector3 normal = Vector3 {0, -1, 0};

                add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

                add_vertex(mesh, triangle_index, vert_index, position, {1, 0, 0}, normal, {texcoords_rect.width, texcoords_rect.y});

                add_vertex(
                    mesh, triangle_index, vert_index, position, {1, 0, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

                add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 0}, normal, {texcoords_rect.x, texcoords_rect.y});

                add_vertex(
                    mesh, triangle_index, vert_index, position, {1, 0, 1}, normal, {texcoords_rect.width, texcoords_rect.height});

                add_vertex(mesh, triangle_index, vert_index, position, {0, 0, 1}, normal, {texcoords_rect.x, texcoords_rect.height});
            }
        }

        std::vector<Model> generate_world_models(std::vector<chunk>& chunks)
        {
            std::vector<Model> models;
            std::vector<Mesh> meshes;
// Generate meshes on multiple threads
#pragma omp for ordered schedule(static, 1)
            for (size_t i = 0; i < chunks.size(); i++) {
                auto&& mesh = chunk_mesh(chunks[i]);
#pragma omp ordered
                meshes.push_back(mesh);
            }

            // Generate models on mono thread (OpenGL)
            for (size_t i = 0; i < meshes.size(); i++) {
                UploadMesh(&meshes[i], false);
                Model world_model = LoadModelFromMesh(meshes[i]);
                models.push_back(world_model);
            }
            return models;
        }

        inline int triangle_count(chunk& _chunk)
        {
            int count = 0;
            auto& blocks = _chunk.get_blocks();

            for (int x = 0; x < chunk::chunk_size_x; x++) {
                for (int y = 0; y < chunk::chunk_size_y; y++) {
                    for (int z = 0; z < chunk::chunk_size_z; z++) {
                        const size_t index =
                            math::convert_to_1d(x, y, z, chunk::chunk_size_x, chunk::chunk_size_y, chunk::chunk_size_z);

                        if (blocks[index].block_type == block_type::air || blocks[index].is_visible == false) {
                            continue;
                        }
                        count += 6;
                    }
                }
            }
            return count;
        }

        Mesh chunk_mesh(chunk& _chunk)
        {
            Mesh mesh = {0};
            mesh.vertexCount = triangle_count(_chunk) * 6;
            mesh.triangleCount = triangle_count(_chunk) * 2;

            mesh.vertices = static_cast<float*>(MemAlloc(sizeof(float) * 3 * mesh.vertexCount));
            mesh.normals = static_cast<float*>(MemAlloc(sizeof(float) * 3 * mesh.vertexCount));
            mesh.texcoords = static_cast<float*>(MemAlloc(sizeof(float) * 2 * mesh.vertexCount));

            size_t triangle_index = 0;
            size_t vert_index = 0;

            auto& blocks = _chunk.get_blocks();

            for (int x = 0; x < chunk::chunk_size_x; x++) {
                for (int y = 0; y < chunk::chunk_size_y; y++) {
                    for (int z = 0; z < chunk::chunk_size_z; z++) {
                        const size_t index =
                            math::convert_to_1d(x, y, z, chunk::chunk_size_x, chunk::chunk_size_y, chunk::chunk_size_z);

                        if (blocks[index].block_type == block_type::air || blocks[index].is_visible == false) {
                            continue;
                        }
                        bool faces[6] = {true, true, true, true, true, true};
                        AddCube(mesh, triangle_index, vert_index, {(float)x, (float)y, (float)z}, faces, 1);
                    }
                }
            }
            return mesh;
        }
};

#endif  // WORLD_OF_CUBE_WORLD_HPP