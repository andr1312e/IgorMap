#version 330
//in vec4 col;
in vec2 Texeles;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float persent;

out vec4 fragColor;

void main() {
    fragColor = mix(texture(ourTexture, Texeles), texture(ourTexture2, Texeles), persent);
}
