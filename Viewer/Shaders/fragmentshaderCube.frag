#version 330
//in vec4 col;
in vec2 Texeles;

uniform sampler2D ourTexture;
uniform vec3 lightColor;

out vec4 color;

void main() {
    float ambeintStrength = 0.1f;
    vec3 ambient = ambeintStrength * lightColor;
    color = vec4(ambient, 1.0f) * texture(ourTexture, Texeles);
}
