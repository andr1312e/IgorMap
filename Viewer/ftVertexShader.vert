#version 330 core
in vec2 vertex;
in vec2 texels;
out vec2 uv;

flat out int level;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform float zcoord;

void main()
{
    gl_Position = proj * view * model * vec4(vertex, zcoord, 1.0);
    uv = texels;
    level = gl_VertexID / 6;
}
