#version 330


flat in uint type;
out vec4 color;



void main()
{
    if(type == 0u)
    {
        color = vec4(0.15,0.6,0.15,1.0);
    }
    else
    {
        color = vec4(0.2, 0.2, 0.78, 1.0);
    }

}