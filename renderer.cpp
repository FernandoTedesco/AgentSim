#include "renderer.h"
#include <SDL3/SDL.h>



void renderGrid(Grid &grid,Terrain &terrain, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 40, 150, 40, 255);
    SDL_RenderFillRects(renderer, terrain.grass.data(),terrain.grass.size());

    SDL_SetRenderDrawColor(renderer, 50, 50, 200, 255);
    SDL_RenderFillRects(renderer, terrain.water.data(),terrain.water.size());
}

void rebuildGrid(Grid &grid,Terrain &terrain)
{
    SDL_FRect current_rect;
    current_rect.w = grid.cell_size;
    current_rect.h = grid.cell_size;

    for(int i=0; i<grid.grid_size; i++)
    {
       switch(grid.terrain[i])
       {
        case 0:
        {
            current_rect.x = (i % grid.width) * grid.cell_size; 
            current_rect.y = (i / grid.width) * grid.cell_size;
            terrain.grass.push_back(current_rect);
            break;
        }

        case 1:
        {
            current_rect.x = (i % grid.width) * grid.cell_size; 
            current_rect.y = (i / grid.width) * grid.cell_size;
            terrain.water.push_back(current_rect);
            break;
        }
       }
    
       
    }
    
}


