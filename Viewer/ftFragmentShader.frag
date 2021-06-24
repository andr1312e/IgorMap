#version 330 core
in vec2 uv;
out vec4 color;

//uniform sampler2D texture0;
 uniform sampler2DArray textureArray;
uniform vec3 textureColor;
uniform int offsetInMyBlock;

const int MY_ARRAY_SIZE = 500;
layout (std140) uniform myblock
{
    vec4 myarray[MY_ARRAY_SIZE];
};

flat in int level;

void main()
{
    int currentLevel = offsetInMyBlock + level;
    //vec4 sampled = vec4(1.0, 1.0, 1.0, texture(texture0, textureCoodrs).r);
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(textureArray,
                                               vec3(uv, myarray[currentLevel / 4][currentLevel % 4])).r);
    color = vec4(textureColor, 1.0) * sampled;
}
