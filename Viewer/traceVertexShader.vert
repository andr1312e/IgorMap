#version 330
in vec3 posAttr;
//out vec4 objectColor;

uniform mat4 mvp;
uniform float zcoord;

void main() {
    gl_Position = mvp * vec4(posAttr.xy, zcoord, 1.0);
}
