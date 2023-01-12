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

    uint32_t chunk_size = world_chunk_size_x * world_chunk_size_y * world_chunk_size_z;
    chunks = std::vector<chunk>(chunk_size, chunk());

    gen.generate_word(
        chunks, world_chunk_start_x, world_chunk_start_y, world_chunk_start_z, world_chunk_size_x, world_chunk_size_y, world_chunk_size_z, true);
}

void world::generate_world_models()
{
    // Free the models
    chunks_model.clear();
    chunks_model.shrink_to_fit();
    
    std::cout << "Generating world models" << std::endl;
    chunks_model = std::move(world_md.generate_world_models(chunks));
}