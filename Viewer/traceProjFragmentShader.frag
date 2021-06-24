#version 430
//in vec4 objectColor;
out vec4 color;

uniform vec4 objectColor;

void main() {
    color = objectColor;//vec4(0.6,0.6,0.6,1.);
}
