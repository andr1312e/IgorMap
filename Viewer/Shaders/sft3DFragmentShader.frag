#version 330 core
in vec2 textureCoodrs;
out vec4 color;

uniform sampler2D texture0;
uniform vec4 textureColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture0, textureCoodrs).r);
    color = vec4(textureColor) * sampled;
}
