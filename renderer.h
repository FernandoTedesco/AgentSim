#pragma once
#include "grid.h"
#include <SDL3/SDL.h>
#include <vector>
#include <glad/gl.h>
#include "parameters.h"
#include "camera.h"
struct Cell
{
    int x;
    int y;
};

struct Type
{
    uint8_t type; //1 = grass 2 = water
};


struct Terrain
{
    std::vector<Cell>cell_pos;
    std::vector<Type>cell_type;

};



void renderGrid(Grid &grid, Camera camera, GL_State gl_state);


