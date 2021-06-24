#version 330
in vec3 vertex;
in vec3 texels;
out vec3 uv;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(vertex.xyz, 1.0);
    uv = texels;
}
