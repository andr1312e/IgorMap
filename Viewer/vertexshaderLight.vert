#version 330
in vec4 posAttr;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main() {   
   gl_Position = proj * view * model * posAttr;   
}
