#version 330
in vec3 posAttr;

uniform mat4 mvp;

void main() {
    gl_Position = mvp * vec4(posAttr.xyz, 1.0);
}
