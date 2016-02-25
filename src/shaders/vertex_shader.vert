
#version 330 core

in vec3 position;
in vec2 texture_coords;

out vec2 pass_texture_coords;

void main(void)
{
    gl_Position = vec4(position, 1.0);
    pass_texture_coords = texture_coords;
}
