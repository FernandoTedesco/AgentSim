#include <SDL3/SDL.h>
#include "grid.h"
#include "renderer.h"
#include "parameters.h"
#include "camera.h"
#include <glad/gl.h>
#include <iostream>
#include <fstream>
#include <sstream>


GLuint compileShader(GLenum type, const char* string)
{
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &string, nullptr);
        glCompileShader(shader);

        GLint compiled;
        glGetShaderiv(shader,GL_COMPILE_STATUS, &compiled);
        if(!compiled)
        {
            char log[1024];
            glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
            SDL_Log("shader: %s", log);
            return 0;
        }
        return shader;

}

int main()
{



    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        
        SDL_Log("%s",SDL_GetError());
        return 1;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); 
    

    SDL_Window *window = SDL_CreateWindow("Gpu_agents", 1200, 800,SDL_WINDOW_OPENGL);
    if(window == nullptr)
    {
        SDL_Log("%s",SDL_GetError());
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if(context == NULL)
    {
        SDL_Log("%s",SDL_GetError());
        return 1;
    }
    if(!SDL_GL_SetSwapInterval(1))
    {
        SDL_Log("vsync: %s", SDL_GetError());
    }


    gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);

    std::ifstream vertex_file("/home/ftedesco/Desktop/Projects/GPU_agents/vertex.vert");
    std::stringstream vertex_stream;
    vertex_stream << vertex_file.rdbuf();
    std::string vertex_string = vertex_stream.str();

    std::ifstream fragment_file("/home/ftedesco/Desktop/Projects/GPU_agents/fragment.frag");
    std::stringstream fragment_stream;
    fragment_stream << fragment_file.rdbuf();
    std::string fragment_string = fragment_stream.str();


    GLuint vertex_shader = compileShader(GL_VERTEX_SHADER, vertex_string.c_str());
    if(!vertex_shader)
    {
        return 0;
    }
    GLuint fragment_shader = compileShader(GL_FRAGMENT_SHADER, fragment_string.c_str());
    if(!fragment_shader)
    {
        return 0;
    }
    GLuint shader = glCreateProgram();
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);

    GLint linked;
    glGetProgramiv(shader, GL_LINK_STATUS, &linked);
    if(!linked)
    {
    


        char log[1024];
        glGetProgramInfoLog(shader, sizeof(log), nullptr, log);
        SDL_Log("link: %s", log);
        return 1;
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    GL_State gl_state;
    gl_state.shader = shader;
    gl_state.u_camera = glGetUniformLocation(shader, "u_camera");
    gl_state.u_grid_width = glGetUniformLocation(shader, "u_grid_width");
    gl_state.u_cell_size = glGetUniformLocation(shader, "u_cell_size");
    gl_state.u_view_size = glGetUniformLocation(shader, "u_view_size");



    Grid grid;
    grid.width = parameters::grid_width;
    grid.height = parameters::grid_height;
    grid.cell_size = parameters::cell_size;
    
    
    Terrain terrain;
    

    buildGrid(grid);
    

    //
    Camera camera;
    camera.x = grid.width * grid.cell_size * 0.5f;
    camera.y = grid.height * grid.cell_size * 0.5f;


    //gl
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, grid.terrain.size()* sizeof(grid.terrain[0]),grid.terrain.data(),GL_STATIC_DRAW);

    glVertexAttribIPointer(0,1,GL_UNSIGNED_BYTE, sizeof(uint8_t), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribDivisor(0,1);

    glBindVertexArray(0);
    gl_state.vao = vao;



    
    

    glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
    Uint64 last_time = SDL_GetTicksNS();
    bool running = true;
    SDL_Event event;
    Uint64 last_tick = SDL_GetTicks();
    int frames = 0;
    while(running)
    {
        Uint64 now_time = SDL_GetTicksNS();
        float dt = (now_time - last_time)/1000000000.0f;
        last_time = now_time;
        const bool *keys=SDL_GetKeyboardState(nullptr);

        if(keys[SDL_SCANCODE_W]) camera.y -= normal_speed * dt;
        if(keys[SDL_SCANCODE_S]) camera.y += normal_speed * dt;
        if(keys[SDL_SCANCODE_A]) camera.x -= normal_speed * dt;
        if(keys[SDL_SCANCODE_D]) camera.x += normal_speed * dt;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }

        }
        

        glClear(GL_COLOR_BUFFER_BIT);
        renderGrid(grid, camera, gl_state);
        SDL_GL_SwapWindow(window);
        frames++;
        Uint64 now = SDL_GetTicks();
        
        
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return 0;

}