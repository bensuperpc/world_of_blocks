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

#define MAX_MESH_VBO 7

class world_model
{
    public:
        world_model() {}

        ~world_model() {}

    const std::array<float, 12> texcoords_ref_front = {
        0.5f, 1.0f,
        0.25f, 1.0f,
        0.25f, 0.0f,

        0.25f, 0.0f,
        0.5f, 0.0f,
        0.5f, 1.0f,
    };

    const std::array<float, 12> texcoords_ref_back = {
        0.25f, 1.0f,
        0.25f, 0.0f,
        0.5f, 0.0f,

        0.5f, 0.0f,
        0.5f, 1.0f,
        0.25f, 1.0f,
    };

    const std::array<float, 12> texcoords_ref_top = {
        0.0f, 0.0f,
        0.25f, 0.0f,
        0.25f, 1.0f,

        0.25f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
    };

    const std::array<float, 12> texcoords_ref_bottom = {
        0.0f, 0.0f,
        0.25f, 0.0f,
        0.25f, 1.0f,

        0.25f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
    };

    const std::array<float, 12> texcoords_ref_right = {
        0.25f, 1.0f,
        0.25f, 0.0f,
        0.5f, 0.0f,

        0.5f, 0.0f,
        0.5f, 1.0f,
        0.25f, 1.0f,
    };

    const std::array<float, 12> texcoords_ref_left = {
        0.5f, 1.0f,
        0.25f, 1.0f,
        0.25f, 0.0f,

        0.25f, 0.0f,
        0.5f, 0.0f,
        0.5f, 1.0f,
    };

    const std::array<float, 18> normals_ref_front ={
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };

    const std::array<float, 18> normals_ref_back ={
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,

        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
    };

    const std::array<float, 18> normals_ref_top ={
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    const std::array<float, 18> normals_ref_bottom ={
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,

        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
    };

    const std::array<float, 18> normals_ref_right ={
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };

    const std::array<float, 18> normals_ref_left ={
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
    };

    static std::vector<float> get_cube_vertices_front(float x, float y, float z)
    {
        const float width = 1.0f;
            const float height = 1.0f;
            const float length = 1.0f;
            // 108 vertices
            std::vector<float> cubeVertices = {
                -width / 2 + x, -height / 2 + y, length / 2 + z,
                width / 2 + x, -height / 2 + y, length / 2 + z,
                width / 2 + x, height / 2 + y, length / 2 + z,

                width / 2 + x, height / 2 + y, length / 2 + z,
                -width / 2 + x, height / 2 + y, length / 2 + z,
                -width / 2 + x, -height / 2 + y, length / 2 + z,};
        
        return cubeVertices;
    }

    static std::vector<float> get_cube_vertices_back(float x, float y, float z)
    {
        const float width = 1.0f;
            const float height = 1.0f;
            const float length = 1.0f;
            // 108 vertices
            std::vector<float> cubeVertices = {
                -width / 2 + x, -height / 2 + y, -length / 2 + z,
                -width / 2 + x, height / 2 + y, -length / 2 + z,
                width / 2 + x, height / 2 + y, -length / 2 + z,

                width / 2 + x, height / 2 + y, -length / 2 + z,
                width / 2 + x, -height / 2 + y, -length / 2 + z,
                -width / 2 + x, -height / 2 + y, -length / 2 + z};
        
        return cubeVertices;
    }

    static std::vector<float> get_cube_vertices_top(float x, float y, float z)
    {
        const float width = 1.0f;
            const float height = 1.0f;
            const float length = 1.0f;
            // 108 vertices
            std::vector<float> cubeVertices = {
                -width / 2 + x, height / 2 + y, -length / 2 + z,
                -width / 2 + x, height / 2 + y, length / 2 + z,
                width / 2 + x, height / 2 + y, length / 2 + z,

                width / 2 + x, height / 2 + y, length / 2 + z,
                width / 2 + x, height / 2 + y, -length / 2 + z,
                -width / 2 + x, height / 2 + y, -length / 2 + z,};
        
        return cubeVertices;
    }

    static std::vector<float> get_cube_vertices_bottom(float x, float y, float z)
    {
        const float width = 1.0f;
            const float height = 1.0f;
            const float length = 1.0f;
            // 108 vertices
            std::vector<float> cubeVertices = {
                -width / 2 + x, -height / 2 + y, -length / 2 + z,
                width / 2 + x, -height / 2 + y, -length / 2 + z,
                width / 2 + x, -height / 2 + y, length / 2 + z,

                width / 2 + x, -height / 2 + y, length / 2 + z,
                -width / 2 + x, -height / 2 + y, length / 2 + z,
                -width / 2 + x, -height / 2 + y, -length / 2 + z,};
        
        return cubeVertices;
    }

    static std::vector<float> get_cube_vertices_right(float x, float y, float z)
    {
        const float width = 1.0f;
            const float height = 1.0f;
            const float length = 1.0f;
            // 108 vertices
            std::vector<float> cubeVertices = {
                width / 2 + x, -height / 2 + y, -length / 2 + z,
                width / 2 + x, height / 2 + y, -length / 2 + z,
                width / 2 + x, height / 2 + y, length / 2 + z,

                width / 2 + x, height / 2 + y, length / 2 + z,
                width / 2 + x, -height / 2 + y, length / 2 + z,
                width / 2 + x, -height / 2 + y, -length / 2 + z,};
        
        return cubeVertices;
    }

    static std::vector<float> get_cube_vertices_left(float x, float y, float z)
    {
        const float width = 1.0f;
            const float height = 1.0f;
            const float length = 1.0f;
            // 108 vertices
            std::vector<float> cubeVertices = {
                -width / 2 + x, -height / 2 + y, -length / 2 + z,
                -width / 2 + x, -height / 2 + y, length / 2 + z,
                -width / 2 + x, height / 2 + y, length / 2 + z,

                -width / 2 + x, height / 2 + y, length / 2 + z,
                -width / 2 + x, height / 2 + y, -length / 2 + z,
                -width / 2 + x, -height / 2 + y, -length / 2 + z,};
        
        return cubeVertices;
    }

    // Original c function: https://github.com/pietmichal/raycraft/blob/master/src/world/worldmodel.c
    Mesh chunk_mesh(chunk & _chunk)
    {
        Mesh mesh = {0};
        mesh.vboId = (unsigned int *)RL_CALLOC(MAX_MESH_VBO, sizeof(unsigned int));

        std::vector<float> vertices = std::vector<float>(36 * 3 *chunk::chunk_size_x * chunk::chunk_size_y * chunk::chunk_size_z);
        std::vector<float> texcoords = std::vector<float>(36 * 2 *chunk::chunk_size_x * chunk::chunk_size_y * chunk::chunk_size_z);
        std::vector<float> normals = std::vector<float>(36 * 3 *chunk::chunk_size_x * chunk::chunk_size_y * chunk::chunk_size_z);

        // +z
        bool front = true;
        // -z
        bool back = true;
        // +y
        bool top = true;
        // -y
        bool bottom = true;
        // +x
        bool right = true;
        // -x
        bool left = true;

        int verticesCount = 0;
        int texcoordsCount = 0;
        int normalsCount = 0;

        auto& blocks = _chunk.get_blocks();

        for (size_t i = 0; i < blocks.size(); i++) {
            block& current_block = blocks[i];

            if (current_block.block_type == block_type::air || current_block.is_visible == false)
            {
                continue;
            }

            const int z = i / (chunk::chunk_size_x * chunk::chunk_size_y);
            const int y = (i - (z * chunk::chunk_size_x * chunk::chunk_size_y)) / chunk::chunk_size_x;
            const int x = i - (z * chunk::chunk_size_x * chunk::chunk_size_y) - (y * chunk::chunk_size_x);

            // Vertices
            const auto && block_vertices_front = get_cube_vertices_front(x, y, z);
            const auto && block_vertices_back = get_cube_vertices_back(x, y, z);
            const auto && block_vertices_top = get_cube_vertices_top(x, y, z);
            const auto && block_vertices_bottom = get_cube_vertices_bottom(x, y, z);
            const auto && block_vertices_right = get_cube_vertices_right(x, y, z);
            const auto && block_vertices_left = get_cube_vertices_left(x, y, z);

            for (int v = 0; v < 18; v++)
            {
                if(front) {
                    vertices[verticesCount + v + 0] = block_vertices_front[v];
                }
                if(back) {
                    vertices[verticesCount + v + 18] = block_vertices_back[v];
                }
                if(top) {
                    vertices[verticesCount + v + 36] = block_vertices_top[v];
                }
                if(bottom) {
                    vertices[verticesCount + v + 54] = block_vertices_bottom[v];
                }
                if(right) {
                    vertices[verticesCount + v + 72] = block_vertices_right[v];
                }
                if(left) {
                    vertices[verticesCount + v + 90] = block_vertices_left[v];
                }
            }
            
            // Texture coordinates
            for (int t = 0; t < 12; t++)
            {
                if(front) {
                    texcoords[texcoordsCount + t + 0] = texcoords_ref_front[t];
                }
                if(back) {
                    texcoords[texcoordsCount + t + 12] = texcoords_ref_back[t];
                }
                if(top) {
                    texcoords[texcoordsCount + t + 24] = texcoords_ref_top[t];
                }
                if(bottom) {
                    texcoords[texcoordsCount + t + 36] = texcoords_ref_bottom[t];
                }
                if(right) {
                    texcoords[texcoordsCount + t + 48] = texcoords_ref_right[t];
                }
                if(left) {
                    texcoords[texcoordsCount + t + 60] = texcoords_ref_left[t];
                }
            }

            // Normals
            for (int n = 0; n < 18; n++)
            {
                if (front) {
                    normals[normalsCount + n + 0] = normals_ref_front[n];
                }
                if (back) {
                    normals[normalsCount + n + 18] = normals_ref_back[n];
                }
                if (top) {
                    normals[normalsCount + n + 36] = normals_ref_top[n];
                }
                if (bottom) {
                    normals[normalsCount + n + 54] = normals_ref_bottom[n];
                }
                if (right) {
                    normals[normalsCount + n + 72] = normals_ref_right[n];
                }
                if (left) {
                    normals[normalsCount + n + 90] = normals_ref_left[n];
                }
            }

            if (front) {
                verticesCount += 18;
                texcoordsCount += 12;
                normalsCount += 18;
            }
            if (back) {
                verticesCount += 18;
                texcoordsCount += 12;
                normalsCount += 18;
            }
            if (top) {
                verticesCount += 18;
                texcoordsCount += 12;
                normalsCount += 18;
            }
            if (bottom) {
                verticesCount += 18;
                texcoordsCount += 12;
                normalsCount += 18;
            }
            if (right) {
                verticesCount += 18;
                texcoordsCount += 12;
                normalsCount += 18;
            }
            if (left) {
                verticesCount += 18;
                texcoordsCount += 12;
                normalsCount += 18;
            }
        }
        
        /*
        //#pragma omp parallel for collapse(3) schedule(auto)
        for (int x = 0; x < chunk::chunk_size_x; x++)
        {
            for (int y = 0; y < chunk::chunk_size_y; y++)
            {
                for (int z = 0; z < chunk::chunk_size_z; z++)
                {
                    const size_t index = math::convert_to_1d(x, y, z, chunk::chunk_size_x, chunk::chunk_size_y, chunk::chunk_size_z);
                    
                    if (blocks[index].block_type == block_type::air || blocks[index].is_visible == false)
                    {
                        continue;
                    }
                    
                    // Vertices
                    const auto && block_vertices_front = get_cube_vertices_front(x, y, z);
                    const auto && block_vertices_back = get_cube_vertices_back(x, y, z);
                    const auto && block_vertices_top = get_cube_vertices_top(x, y, z);
                    const auto && block_vertices_bottom = get_cube_vertices_bottom(x, y, z);
                    const auto && block_vertices_right = get_cube_vertices_right(x, y, z);
                    const auto && block_vertices_left = get_cube_vertices_left(x, y, z);

                    for (int v = 0; v < 18; v++)
                    {
                        if(front) {
                            vertices[verticesCount + v + 0] = block_vertices_front[v];
                        }
                        if(back) {
                            vertices[verticesCount + v + 18] = block_vertices_back[v];
                        }
                        if(top) {
                            vertices[verticesCount + v + 36] = block_vertices_top[v];
                        }
                        if(bottom) {
                            vertices[verticesCount + v + 54] = block_vertices_bottom[v];
                        }
                        if(right) {
                            vertices[verticesCount + v + 72] = block_vertices_right[v];
                        }
                        if(left) {
                            vertices[verticesCount + v + 90] = block_vertices_left[v];
                        }
                    }

                    // Texture coordinates
                    for (int t = 0; t < 12; t++)
                    {
                        if(front) {
                            texcoords[texcoordsCount + t + 0] = texcoords_ref_front[t];
                        }
                        if(back) {
                            texcoords[texcoordsCount + t + 12] = texcoords_ref_back[t];
                        }
                        if(top) {
                            texcoords[texcoordsCount + t + 24] = texcoords_ref_top[t];
                        }
                        if(bottom) {
                            texcoords[texcoordsCount + t + 36] = texcoords_ref_bottom[t];
                        }
                        if(right) {
                            texcoords[texcoordsCount + t + 48] = texcoords_ref_right[t];
                        }
                        if(left) {
                            texcoords[texcoordsCount + t + 60] = texcoords_ref_left[t];
                        }
                    }

                    // Normals
                    for (int n = 0; n < 18; n++)
                    {
                        if (front) {
                            normals[normalsCount + n + 0] = normals_ref_front[n];
                        }
                        if (back) {
                            normals[normalsCount + n + 18] = normals_ref_back[n];
                        }
                        if (top) {
                            normals[normalsCount + n + 36] = normals_ref_top[n];
                        }
                        if (bottom) {
                            normals[normalsCount + n + 54] = normals_ref_bottom[n];
                        }
                        if (right) {
                            normals[normalsCount + n + 72] = normals_ref_right[n];
                        }
                        if (left) {
                            normals[normalsCount + n + 90] = normals_ref_left[n];
                        }
                    }

                    if (front) {
                        verticesCount += 18;
                        texcoordsCount += 12;
                        normalsCount += 18;
                    }
                    if (back) {
                        verticesCount += 18;
                        texcoordsCount += 12;
                        normalsCount += 18;
                    }
                    if (top) {
                        verticesCount += 18;
                        texcoordsCount += 12;
                        normalsCount += 18;
                    }
                    if (bottom) {
                        verticesCount += 18;
                        texcoordsCount += 12;
                        normalsCount += 18;
                    }
                    if (right) {
                        verticesCount += 18;
                        texcoordsCount += 12;
                        normalsCount += 18;
                    }
                    if (left) {
                        verticesCount += 18;
                        texcoordsCount += 12;
                        normalsCount += 18;
                    }
                }
            }
        }
        */
        
        mesh.vertices = (float *)RL_MALLOC(verticesCount * sizeof(float));
        memcpy(mesh.vertices, vertices.data(), verticesCount * sizeof(float));
        //std::copy_n(vertices.data(), verticesCount, mesh.vertices);
        
        mesh.texcoords = (float *)RL_MALLOC(texcoordsCount * sizeof(float));
        memcpy(mesh.texcoords, texcoords.data(), texcoordsCount * sizeof(float));
        //std::copy_n(texcoords.data(), texcoordsCount, mesh.texcoords);

        mesh.normals = (float *)RL_MALLOC(normalsCount * sizeof(float));
        memcpy(mesh.normals, normals.data(), normalsCount * sizeof(float));
        //std::copy_n(normals.data(), normalsCount, mesh.normals);

        mesh.vertexCount = verticesCount / 3;
        mesh.triangleCount = (verticesCount / 3) / 2;
        return mesh;
    }

    std::vector<Model> generate_world_models(std::vector<chunk> &chunks)
    {
        std::vector<Model> models;
        std::vector<Mesh> meshes;
        // Generate meshes on multiple threads
        #pragma omp for ordered schedule(static,1)
        for (size_t i = 0; i < chunks.size(); i++)
        {
            auto&& mesh = chunk_mesh(chunks[i]);
            #pragma omp ordered
            meshes.push_back(mesh);
        }

        // Generate models on mono thread (OpenGL)
        for (size_t i = 0; i < meshes.size(); i++)
        {
            UploadMesh(&meshes[i], false);
            Model worldModel = LoadModelFromMesh(meshes[i]);
            models.push_back(worldModel);
        }
        return models;
    }
};

#endif  // WORLD_OF_CUBE_WORLD_HPP