#version 330 core
in vec2 vertex;
in vec2 texels;
out vec2 textureCoodrs;

uniform mat4 mvp;
uniform float zcoord;

void main()
{
    gl_Position = mvp * vec4(vertex, zcoord, 1.0);
    textureCoodrs = texels;
}
