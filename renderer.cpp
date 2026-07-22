#include "renderer.h"
#include <SDL3/SDL.h>
#include <vector>
#include "camera.h"
#include "math.h"
void renderGrid(Grid &grid, Camera camera,  GL_State gl_state)
{
 
    glUseProgram(gl_state.shader);

    glUniform2f(gl_state.u_camera, roundf(camera.x), roundf(camera.y));
    glUniform2f(gl_state.u_view_size, 1200.0f, 800.0f);
    glUniform1f(gl_state.u_cell_size, (float)grid.cell_size);
    glUniform1i(gl_state.u_grid_width, grid.width);

    glBindVertexArray(gl_state.vao);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, grid.grid_size);


}


