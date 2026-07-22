#version 330

uniform vec2 u_camera;
uniform vec2 u_view_size;
uniform float u_cell_size;
uniform int u_grid_width;

layout(location = 0) in uint a_type;

flat out uint type;

void main()
{
  
    
    type = a_type;
    //o = origin, c = corner
    vec2 o = vec2(gl_InstanceID % u_grid_width, gl_InstanceID/u_grid_width)*u_cell_size;
    vec2 c = vec2(gl_VertexID & 1, gl_VertexID>>1)*u_cell_size;
    vec2 sum = o + c;
    vec2 p = (sum - u_camera)/(u_view_size * 0.5);
    gl_Position = vec4(p.x,-p.y, 0.0, 1.0);
}