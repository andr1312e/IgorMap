#version 330 core
in float zCoord;
out vec4 ourColor;

uniform mat4 mvp;

void main()
{
    float x, y, z, zf;
    x = gl_VertexID / 150 + 30;
    y = gl_VertexID % 150 + 30;
    z = 1 + zCoord / 255.;
    zf = zCoord / 255.0;
    gl_Position = mvp * vec4(x, y, z, 1.0);
    ourColor = vec4(zf, 0.0f, 0.0f, 1.0f);
}
