#version 330
in vec2 posAttr;

uniform mat4 mvp;
uniform float zcoord;

void main() {
    //float y = posAttr.y / 100.;
    gl_Position = mvp * vec4(posAttr.xy, zcoord, 1.0);
}
