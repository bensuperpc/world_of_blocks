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
    chunks = std::move(gen.generate_word(
        world_chunk_start_x, world_chunk_start_y, world_chunk_start_z, world_chunk_size_x, world_chunk_size_y, world_chunk_size_z, true));
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "World generation took " << duration.count() << "ms" << std::endl;
}

void world::generate_world_models()
{
    // Free the models
    for (auto& model : chunks_model)
    {
        UnloadModel(model);
    }

    // Free the models
    chunks_model.clear();
    chunks_model.shrink_to_fit();

    std::cout << "Generating world models" << std::endl;
    chunks_model = std::move(world_md.generate_world_models(chunks));
}

void world::generate_chunk(const int32_t x, const int32_t y, const int32_t z)
{
    // Generate the chunk
    auto start = std::chrono::high_resolution_clock::now();
    chunk chunk_new = gen.generate_chunk(x, y, z, false);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Chunk generation took " << duration.count() << "ms" << std::endl;

    // Add the chunk to the world
    chunks.push_back(std::move(chunk_new));

    // Generate the model (TODO: Separate the model generation from the chunk generation)
    chunks_model.push_back(std::move(world_md.generate_chunk_model(chunk_new)));
}


void world::clear()
{
    // Clear the chunks
    chunks.clear();
    chunks.shrink_to_fit();

    // Free the models
    for (auto& model : chunks_model)
    {
        UnloadModel(model);
    }

    // Free the models
    chunks_model.clear();
    chunks_model.shrink_to_fit();
}