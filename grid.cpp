#include "grid.h"

void buildGrid(Grid &grid)
{
    
    grid.grid_size = grid.grid_width * grid.grid_height;

    grid.terrain.assign(grid.grid_size, 0);
    grid.food.assign(grid.grid_size, 0);

}



