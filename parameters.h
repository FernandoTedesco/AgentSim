#pragma once

struct GL_State
{
    GLuint vao;
    GLuint shader;
    GLint u_camera; 
    GLint u_grid_width;
    GLint u_cell_size;
    GLint u_view_size;
};

namespace parameters{

    constexpr int grid_width = 200;
    constexpr int grid_height = 200;
    constexpr int cell_size = 20;
}

