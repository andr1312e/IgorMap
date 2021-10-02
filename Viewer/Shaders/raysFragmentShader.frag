#version 330
//in vec4 objectColor;
out vec4 color;

uniform vec4 objectColor;
uniform int number;

void main() {
    float alpha = 0.1 * (3 - number);
    color = vec4(objectColor.rgb, objectColor.a - alpha);
}
