#pragma once
#include <vector>
#include <cstdint>

struct Pos
{
    int x;
    int y;
};


struct Grid
{
    int width;
    int height;
    int grid_size;
    int cell_size;

    bool grid_dirty;

    std::vector<uint8_t> food;
    std::vector<uint8_t> terrain;
    std::vector<uint8_t> heightmap;
    
};

void buildGrid(Grid &grid);













