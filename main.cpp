#include <SDL3/SDL.h>
#include "grid.h"
#include "renderer.h"
#include "parameters.h"

int main()
{

    

    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        
        SDL_Log("%s",SDL_GetError());
        return 1;
    }
    
    SDL_Window *window = SDL_CreateWindow("Gpu_agents", 1200, 800,0);
    if(window == nullptr)
    {
        SDL_Log("%s",SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,"opengl");
    if(renderer == nullptr)
    {
        SDL_Log("%s",SDL_GetError());
        return 1;
    }
    Grid grid;
    grid.width = parameters::grid_width;
    grid.height = parameters::grid_height;
    grid.cell_size = parameters::cell_size;
    
    Terrain terrain;
    

    buildGrid(grid);
    rebuildGrid(grid, terrain);
    


    bool running = true;
    SDL_Event event;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }


        }
        

        SDL_RenderClear(renderer);
        renderGrid(grid, terrain, renderer);
        SDL_RenderPresent(renderer);


        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return 0;
}