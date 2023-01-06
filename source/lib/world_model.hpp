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


// Original c function: https://github.com/pietmichal/raycraft/blob/master/src/world/worldmodel.c
std::array<float, 72> texcoords_ref = {
    // face 1 (front)
    0.5f, 1.0f,
    0.25f, 1.0f,
    0.25f, 0.0f,

    0.25f, 0.0f,
    0.5f, 0.0f,
    0.5f, 1.0f,


    // face 2 (back)
    0.25f, 1.0f,
    0.25f, 0.0f,
    0.5f, 0.0f,

    0.5f, 0.0f,
    0.5f, 1.0f,
    0.25f, 1.0f,

    // face 3 (top)
    0.0f, 0.0f,
    0.25f, 0.0f,
    0.25f, 1.0f,

    0.25f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    // face 4 (bottom)
    0.0f, 0.0f,
    0.25f, 0.0f,
    0.25f, 1.0f,

    0.25f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    // face 5 (right)
    0.25f, 1.0f,
    0.25f, 0.0f,
    0.5f, 0.0f,

    0.5f, 0.0f,
    0.5f, 1.0f,
    0.25f, 1.0f,

    // face 6 (left)
    0.5f, 1.0f,
    0.25f, 1.0f,
    0.25f, 0.0f,

    0.25f, 0.0f,
    0.5f, 0.0f,
    0.5f, 1.0f,
};

// Original c function: https://github.com/pietmichal/raycraft/blob/master/src/world/worldmodel.c
std::array<float, 108> normals_ref = {
    // face 1 (front)
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,

    // face 2 (back)
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,
    0.0f, 0.0f, -1.0f,

    // face 3 (top)
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,

    // face 4 (bottom)
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,

    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,
    0.0f, -1.0f, 0.0f,

    // face 5 (right)
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    // face 6 (left)
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,

    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f};

// Original c function: https://github.com/pietmichal/raycraft/blob/master/src/world/worldmodel.c
    static std::vector<float> get_cube_vertices(float x, float y, float z)
    {
        // not using indices
        float width = 1.0f;
        float height = 1.0f;
        float length = 1.0f;
        std::vector<float> cubeVertices = std::vector<float>(36 * 3);
        std::array<float, 108> ref = {
            // face 1
            -width / 2 + x, -height / 2 + y, length / 2 + z,
            width / 2 + x, -height / 2 + y, length / 2 + z,
            width / 2 + x, height / 2 + y, length / 2 + z,

            width / 2 + x, height / 2 + y, length / 2 + z,
            -width / 2 + x, height / 2 + y, length / 2 + z,
            -width / 2 + x, -height / 2 + y, length / 2 + z,

            // face 2
            -width / 2 + x, -height / 2 + y, -length / 2 + z,
            -width / 2 + x, height / 2 + y, -length / 2 + z,
            width / 2 + x, height / 2 + y, -length / 2 + z,

            width / 2 + x, height / 2 + y, -length / 2 + z,
            width / 2 + x, -height / 2 + y, -length / 2 + z,
            -width / 2 + x, -height / 2 + y, -length / 2 + z,

            // face 3
            -width / 2 + x, height / 2 + y, -length / 2 + z,
            -width / 2 + x, height / 2 + y, length / 2 + z,
            width / 2 + x, height / 2 + y, length / 2 + z,

            width / 2 + x, height / 2 + y, length / 2 + z,
            width / 2 + x, height / 2 + y, -length / 2 + z,
            -width / 2 + x, height / 2 + y, -length / 2 + z,

            // face 4
            -width / 2 + x, -height / 2 + y, -length / 2 + z,
            width / 2 + x, -height / 2 + y, -length / 2 + z,
            width / 2 + x, -height / 2 + y, length / 2 + z,

            width / 2 + x, -height / 2 + y, length / 2 + z,
            -width / 2 + x, -height / 2 + y, length / 2 + z,
            -width / 2 + x, -height / 2 + y, -length / 2 + z,

            // face 5
            width / 2 + x, -height / 2 + y, -length / 2 + z,
            width / 2 + x, height / 2 + y, -length / 2 + z,
            width / 2 + x, height / 2 + y, length / 2 + z,

            width / 2 + x, height / 2 + y, length / 2 + z,
            width / 2 + x, -height / 2 + y, length / 2 + z,
            width / 2 + x, -height / 2 + y, -length / 2 + z,

            // face 6
            -width / 2 + x, -height / 2 + y, -length / 2 + z,
            -width / 2 + x, -height / 2 + y, length / 2 + z,
            -width / 2 + x, height / 2 + y, length / 2 + z,

            -width / 2 + x, height / 2 + y, length / 2 + z,
            -width / 2 + x, height / 2 + y, -length / 2 + z,
            -width / 2 + x, -height / 2 + y, -length / 2 + z};

        for (int i = 0; i < 36 * 3; i++)
        {
            cubeVertices[i] = ref[i];
        }
        
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
        

        int verticesCount = 0;
        int texcoordsCount = 0;
        int normalsCount = 0;

        auto& blocks = _chunk.get_blocks();
        //#pragma omp parallel for collapse(3) schedule(auto)
        for (int x = 0; x < chunk::chunk_size_x; x++)
        {
            for (int y = 0; y < chunk::chunk_size_y; y++)
            {
                for (int z = 0; z < chunk::chunk_size_z; z++)
                {
                    size_t index = math::convert_to_1d(x, y, z, chunk::chunk_size_x, chunk::chunk_size_y, chunk::chunk_size_z);
                    
                    if (blocks[index].block_type == block_type::air || blocks[index].is_visible == false)
                    {
                        continue;
                    }
                    auto && blockVertices = get_cube_vertices(x, y, z);
                    for (int v = 0; v < 36 * 3; v++)
                    {
                        //#pragma omp critical
                        vertices[verticesCount + v] = blockVertices[v];
                    }
                    for (int t = 0; t < 36 * 2; t++)
                    {
                        texcoords[texcoordsCount + t] = texcoords_ref[t];
                    }
                    for (int n = 0; n < 36 * 3; n++)
                    {
                        normals[normalsCount + n] = normals_ref[n];
                    }
                    verticesCount += 36 * 3;
                    texcoordsCount += 36 * 2;
                    normalsCount += 36 * 3;
                    
                }
            }
        }
        mesh.vertices = (float *)RL_MALLOC(verticesCount * sizeof(float));
        memcpy(mesh.vertices, vertices.data(), verticesCount * sizeof(float));

        mesh.texcoords = (float *)RL_MALLOC(texcoordsCount * sizeof(float));
        memcpy(mesh.texcoords, texcoords.data(), texcoordsCount * sizeof(float));

        mesh.normals = (float *)RL_MALLOC(normalsCount * sizeof(float));
        memcpy(mesh.normals, normals.data(), normalsCount * sizeof(float));

        mesh.vertexCount = verticesCount / 3;
        mesh.triangleCount = (verticesCount / 3) / 2;

        /*
        UploadMesh(&mesh, false);

        Model worldModel = LoadModelFromMesh(mesh);

        return new Model(worldModel);
        */
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