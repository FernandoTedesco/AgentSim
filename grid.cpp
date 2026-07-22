#include "grid.h"
#include "cstdlib"
#include "ctime"
#include <vector>

std::vector<int> genRiver(Grid &grid, int rivers)
{

    std::vector<int>river_spawns;
    for(int i = 0; i<rivers; i++)
    {
        int random = rand() % grid.terrain.size();
        grid.terrain[random] = 1;
        river_spawns.push_back(random);
    }
    return river_spawns;
}



void buildGrid(Grid &grid)
{
    srand(time(NULL));
    
    grid.grid_size = grid.width * grid.height;

    grid.terrain.assign(grid.grid_size, 0);
    grid.food.assign(grid.grid_size, 0);

    std::vector<int> river_spawns = genRiver(grid, 50);
    



}


