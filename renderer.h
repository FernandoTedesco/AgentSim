#pragma once
#include "grid.h"
#include <SDL3/SDL.h>
#include <vector>

struct Terrain
{
    std::vector<SDL_FRect> grass;
    std::vector<SDL_FRect> water;

};

void rebuildGrid(Grid &grid, Terrain &terrain);

void renderGrid(Grid &grid, Terrain &terrain, SDL_Renderer *renderer);

