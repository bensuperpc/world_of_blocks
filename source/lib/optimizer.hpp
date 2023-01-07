#ifndef WORLD_OF_CUBE_OPTIMIZER_HPP
#define WORLD_OF_CUBE_OPTIMIZER_HPP

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

// Cube lib
#include "block.hpp"

class optimizer
{
    public:
        optimizer() {}

        ~optimizer() {}

        template<typename T = int>
        void optimize(std::vector<block>& blocks,
                      const T begin_x,
                      const T begin_y,
                      const T begin_z,
                      const uint32_t size_x,
                      const uint32_t size_y,
                      const uint32_t size_z)
        {
            constexpr bool debug = false;
            constexpr int debug_x = 20;
            constexpr int debug_y = 31;
            constexpr int debug_z = 25;

            constexpr bool optimize_edges = false;

            const T end_x = static_cast<T>(begin_x + size_x);
            const T end_y = static_cast<T>(begin_y + size_y);
            const T end_z = static_cast<T>(begin_z + size_z);

            if constexpr (debug) {
                std::cout << "optimizing..." << std::endl;
                std::cout << "From (xyz): " << begin_x << ", " << begin_y << ", " << begin_z << std::endl;
                std::cout << "To (xyz): " << end_x << ", " << end_y << ", " << end_z << std::endl;
                std::cout << "Size (xyz): " << size_x << ", " << size_y << ", " << size_z << std::endl;
            }

#pragma omp parallel for schedule(auto)
            for (size_t i = 0; i < blocks.size(); i++) {
                block& current_cube = blocks[i];

                if (current_cube.block_type == block_type::air) {
                    current_cube.is_visible = false;
                    continue;
                }

                if constexpr (debug) {
                    if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                        // #pragma omp critical
                        std::cout << "Block (xyz): " << current_cube.x << ", " << current_cube.y << ", "
                                  << current_cube.z << " current" << std::endl;
                        current_cube.color = raylib::Color::Blue();
                    }
                }

                /*
                int x = i % vecX;
                int y = (i / vecX) % vecY;
                int z = (i / (vecX * vecY)) % vecZ;
                */

                // Count neighbors
                size_t neighbors = 0;
                // Count edges
                size_t edges = 0;

                // x-1
                size_t i1 = i - 1;
                if (i1 < blocks.size()) {
                    if constexpr (debug) {
                        if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                            std::cout << "Block (xyz): " << blocks[i1].x << ", " << blocks[i1].y << ", " << blocks[i1].z
                                      << " index: " << i1
                                      << " block_type: " << block_type::get_name(blocks[i1].block_type) << " x-1"
                                      << std::endl;
                        }
                    }
                    if (current_cube.x > begin_x) {
                        if (blocks[i1].block_type != block_type::air) {
                            neighbors++;
                            if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                                std::cout << "Adding neighbor" << std::endl;
                            }
                        }
                    }
                }
                if (current_cube.x == begin_x) {
                    edges++;
                    if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                        std::cout << "Adding edge" << std::endl;
                    }
                }

                // x+1
                size_t i2 = i + 1;
                if (i2 < blocks.size()) {
                    if constexpr (debug) {
                        if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                            std::cout << "Block (xyz): " << blocks[i2].x << ", " << blocks[i2].y << ", " << blocks[i2].z
                                      << " index: " << i2
                                      << " block_type: " << block_type::get_name(blocks[i2].block_type) << " x+1"
                                      << std::endl;
                        }
                    }
                    if (current_cube.x < end_x - 1) {
                        if (blocks[i2].block_type != block_type::air) {
                            neighbors++;
                            if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                                std::cout << "Adding neighbor" << std::endl;
                            }
                        }
                    }
                }
                if (current_cube.x == end_x - 1) {
                    edges++;
                    if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                        std::cout << "Adding edge" << std::endl;
                    }
                }

                // y-1
                if (current_cube.y == begin_y) {
                    edges++;
                }
                size_t i3 = i - size_x * size_z;
                if (i3 < blocks.size()) {
                    if constexpr (debug) {
                        if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                            std::cout << "Block (xyz): " << blocks[i3].x << ", " << blocks[i3].y << ", " << blocks[i3].z
                                      << " index: " << i3
                                      << " block_type: " << block_type::get_name(blocks[i3].block_type) << " y-1"
                                      << std::endl;
                        }
                    }
                    if (current_cube.y > begin_y) {
                        if (blocks[i3].block_type != block_type::air) {
                            neighbors++;
                            if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                                std::cout << "Adding neighbor" << std::endl;
                            }
                        }
                    }
                }

                // y+1
                size_t i4 = i + size_x * size_z;
                if (i4 < blocks.size()) {
                    if constexpr (debug) {
                        if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                            std::cout << "Block (xyz): " << blocks[i4].x << ", " << blocks[i4].y << ", " << blocks[i4].z
                                      << " index: " << i4
                                      << " block_type: " << block_type::get_name(blocks[i4].block_type) << " y+1"
                                      << std::endl;
                        }
                    }
                    if (current_cube.y < end_y - 1) {
                        if (blocks[i4].block_type != block_type::air) {
                            neighbors++;
                            if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                                std::cout << "Adding neighbor" << std::endl;
                            }
                        }
                    }
                }
                if (current_cube.y == end_y - 1) {
                    edges++;
                    if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                        std::cout << "Adding edge" << std::endl;
                    }
                }

                // z-1
                size_t i5 = i - size_x;
                if (i5 < blocks.size()) {
                    if constexpr (debug) {
                        if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                            std::cout << "Block (xyz): " << blocks[i5].x << ", " << blocks[i5].y << ", " << blocks[i5].z
                                      << " index: " << i5
                                      << " block_type: " << block_type::get_name(blocks[i5].block_type) << " z-1"
                                      << std::endl;
                        }
                    }
                    if (current_cube.z > begin_z) {
                        if (blocks[i5].block_type != block_type::air) {
                            neighbors++;
                            if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                                std::cout << "Adding neighbor" << std::endl;
                            }
                        }
                    }
                }
                if (current_cube.z == begin_z) {
                    edges++;
                    if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                        std::cout << "Adding edge" << std::endl;
                    }
                }

                // z+1
                size_t i6 = i + size_x;
                if (i6 < blocks.size()) {
                    if constexpr (debug) {
                        if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                            std::cout << "Block (xyz): " << blocks[i6].x << ", " << blocks[i6].y << ", " << blocks[i6].z
                                      << " index: " << i6
                                      << " block_type: " << block_type::get_name(blocks[i6].block_type) << " z+1"
                                      << std::endl;
                        }
                    }
                    if (current_cube.z < end_z - 1) {
                        if (blocks[i6].block_type != block_type::air) {
                            neighbors++;
                            if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                                std::cout << "Adding neighbor" << std::endl;
                            }
                        }
                    }
                }
                if (current_cube.z == end_z - 1) {
                    edges++;
                    if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                        std::cout << "Adding edge" << std::endl;
                    }
                }

                if constexpr (optimize_edges) {
                    if (neighbors == 6 && edges == 0) {
                        current_cube.is_visible = false;
                    } else if (neighbors == 5 && edges == 1) {
                        current_cube.is_visible = false;
                    } else if (neighbors == 4 && edges == 2) {
                        current_cube.is_visible = false;
                    } else if (neighbors == 3 && edges == 3) {
                        current_cube.is_visible = false;
                    } else if (neighbors == 2 && edges == 4) {
                        current_cube.is_visible = false;
                    } else if (neighbors == 1 && edges == 5) {
                        current_cube.is_visible = false;
                    } else if (neighbors == 0 && edges == 6) {
                        current_cube.is_visible = false;
                    } else {
                        current_cube.is_visible = true;
                    }
                } else {
                    if (neighbors == 6) {
                        current_cube.is_visible = false;
                    }
                }

                // for debug
                current_cube.neighbors = neighbors;
                current_cube.edges = edges;

                if constexpr (debug) {
                    if (current_cube.x == debug_x && current_cube.y == debug_y && current_cube.z == debug_z && debug) {
                        std::cout << "Neighbors: " << neighbors << std::endl;
                        std::cout << "Edges: " << edges << std::endl;
                        std::cout << std::endl;
                    }
                }
            }
        }
};

#endif  // WORLD_OF_CUBE_OPTIMIZER_HPP