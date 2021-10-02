#version 330 core
in vec3 uv;
out vec4 color;

uniform sampler2DArray textureArray;
uniform vec4 textureColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(textureArray, uv).r);
    if (sampled.a < 0.05) {
        discard;
    }
    else
        color = textureColor * sampled;
}
