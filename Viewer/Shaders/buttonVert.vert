#version 330 core
in vec3 posAttr;

uniform mat4 mvp;

flat out int itemNumber;

void main()
{
    gl_Position = mvp * vec4(posAttr, 1.0);
    itemNumber = gl_VertexID / 6;
}
