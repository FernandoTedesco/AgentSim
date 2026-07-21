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


void simRiver(Grid &grid, std::vector<int> river_spawns)
{
    bool has_ended;
    int river_size;
    int current_pos;
    for(int i = 0; i<river_spawns.size(); i++)
    {
        
        river_size = rand()%1000;
        has_ended = false;
        current_pos = river_spawns[i];
        while(!has_ended)
        {
            int k = rand()%100; //direction: 80% front, 10% to the sides
            river_size--;
            if(current_pos+1 > grid.terrain.size()|| river_size <= 0 || current_pos<0 || current_pos+grid.width>grid.terrain.size())
            {
                has_ended = true;
                break;
            }
            if(k>0 && k<=10)
            {
                grid.terrain[current_pos-1] = 1;
                current_pos -= 1;
            }
            else if(k>10 && k<=20)
            {
                grid.terrain[current_pos+1] = 1;
                current_pos += 1;
            }
            else
            {
                grid.terrain[current_pos+grid.width] = 1;
                current_pos += grid.width;
            }
            
        }
        
    }

}

void buildGrid(Grid &grid)
{
    srand(time(NULL));
    
    grid.grid_size = grid.width * grid.height;

    grid.terrain.assign(grid.grid_size, 0);
    grid.food.assign(grid.grid_size, 0);

    std::vector<int> river_spawns = genRiver(grid, 50);
    
    simRiver(grid, river_spawns);



}


