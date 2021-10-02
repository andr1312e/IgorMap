#version 330
in vec3 posAttr;
//out vec4 objectColor;

uniform mat4 mvp;
uniform int number;

void main() {
    float z = 0.1 * (3 - number);
    gl_Position = mvp * vec4(posAttr.xy, posAttr.z /*- z*/, 1.0);
}
