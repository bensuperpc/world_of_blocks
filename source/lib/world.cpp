#include "world.hpp"

world::world() {}

world::~world() {}

void world::generate_world()
{
    std::cout << "Generating world" << std::endl;
    // Clear the chunks
    chunks.clear();
    chunks.shrink_to_fit();

    // Generate new perlin noise
    gen.reseed(this->seed);

    // Generate the world
    auto start = std::chrono::high_resolution_clock::now();

    for (int32_t x = world_chunk_start_x; x < world_chunk_start_x + world_chunk_size_x; x++) {
        for (int32_t y = world_chunk_start_y; y < world_chunk_start_y + world_chunk_size_y; y++) {
            for (int32_t z = world_chunk_start_z; z < world_chunk_start_z + world_chunk_size_z; z++) {
                generate_chunk(x, y, z, false);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "World generation took " << duration.count() << "ms" << std::endl;
}

void world::generate_world_models()
{
    // Free the models
    for (auto& model : chunks_model) {
        UnloadModel(model);
    }

    // Free the models
    chunks_model.clear();
    chunks_model.shrink_to_fit();

    std::cout << "Generating world models" << std::endl;
    chunks_model = std::move(world_md.generate_world_models(chunks));
}

void world::generate_chunk(const int32_t x, const int32_t y, const int32_t z, bool generate_model)
{
    // Generate the chunk
    auto start = std::chrono::high_resolution_clock::now();
    chunk chunk_new = gen.generate_chunk(x, y, z, true);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Chunk generation took " << duration.count() << "ms" << std::endl;

    // Add the chunk to the world
    chunks.push_back(std::move(chunk_new));

    if (generate_model) {
        start = std::chrono::high_resolution_clock::now();
        // Generate the model (TODO: Separate the model generation from the chunk generation)
        chunks_model.push_back(std::move(world_md.generate_chunk_model(chunk_new)));
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Chunk model generation took " << duration.count() << "ms" << std::endl;
    }
}

bool world::is_chunk_exist(const int32_t x, const int32_t y, const int32_t z)
{
    auto it = std::find_if(chunks.begin(),
                           chunks.end(),
                           [&](const auto& chunk)
                           {
                               const auto chunk_pos = chunk.get_position();
                               return chunk_pos.x == x && chunk_pos.y == y && chunk_pos.z == z;
                           });

    return it != chunks.end();
}

void world::clear()
{
    // Clear the chunks
    chunks.clear();
    chunks.shrink_to_fit();

    // Free the models
    for (auto& model : chunks_model) {
        UnloadModel(model);
    }

    // Free the models
    chunks_model.clear();
    chunks_model.shrink_to_fit();
}