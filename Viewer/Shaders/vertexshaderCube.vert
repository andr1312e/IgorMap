#version 330
in vec4 posAttr;
in vec2 texel;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

//out vec4 col;
out vec2 Texeles;

void main() {
   //col = vec4(1.0f,1.0f,1.0f,1.0f);
   gl_Position = proj * view * model * posAttr;
   Texeles = texel;
}
