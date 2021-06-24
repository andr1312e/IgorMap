#version 330

in float posAttr; //(x,y,amp)

uniform mat4 mvp;

flat out vec4 nullPoint;

void main() {

    gl_Position = mvp * vec4(posAttr, 0., 1., 1.0);
    nullPoint = mvp * vec4(0., 0., 1., 1.0);

    gl_PointSize = 5;
}
