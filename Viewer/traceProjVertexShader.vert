#version 430
in vec3 posAttr;
//out vec4 objectColor;

uniform mat4 mvp;
uniform float zcoord;


void main() {
    gl_Position = mvp * vec4(posAttr.xyz, 1.0);
}
