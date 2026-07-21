#pragma once
#include <vector>
#include <cstdint>

struct Grid
{
    int grid_width;
    int grid_height;
    int grid_size;
    int cell_size;

    bool grid_dirty;

    std::vector<uint8_t> food;
    std::vector<uint8_t> terrain;
    
};

void buildGrid(Grid &grid);












