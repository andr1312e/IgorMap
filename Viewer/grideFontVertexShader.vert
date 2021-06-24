#version 330
in vec2 vertex;
in vec3 texels;
out vec3 uv;

uniform mat4 mvp;
uniform float zcoord;

void main() {
    gl_Position = mvp * vec4(vertex.xy, zcoord, 1.0);
    uv = texels;
}
