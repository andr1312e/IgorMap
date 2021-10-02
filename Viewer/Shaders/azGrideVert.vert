#version 330

in vec2 posAttr; //(x,y,amp)

uniform mat4 mvp;

//flat out vec4 nullPoint;

void main() {

    gl_Position = mvp * vec4(posAttr.xy, 1., 1.0);
    //nullPoint = mvp * vec4(0., 0., 1., 1.0);

    //gl_PointSize = 5;
}
