#version 330

in vec3 posAttr; //(x,y,amp)
//in float msec;

//flat out int reject;
out vec4 outColor;

uniform mat4 mvp;
uniform float ranges[4];
uniform vec4 colors[4];
//uniform float pointSize;
//uniform float az[10];
//uniform float ugm;
//uniform float distStep;
uniform float z;
uniform float alpha;
//uniform int N;

void main() {
    const float PI = 3.14159265359;
    /*int dTime = current_msec - int(msec);
    float dt = float(dTime) / float(numberOfFrameDrawing);
    if (dt > 1)
        dt = 1;
    float dAlpha = 1. - dt;

    float z = posAttr.z - dt;*/
    //int indexAz = gl_VertexID / N;
    //int dist = gl_VertexID % N;
    //float x = dist * distStep * cos((90. - az[indexAz]) * PI / 180.);
    //float y = dist * distStep * sin((90. - az[indexAz]) * PI / 180.);

    gl_Position = mvp * vec4(posAttr.xy, z, 1.0);

    float amp = posAttr.z;

    float pers = 0;
    int index = 0;

    int reject = 0;
    if (amp < ranges[0])
        reject = 1;
    //else if (amp > ranges[3])
    //    reject = 1;

    for (; index != 4; index++) {
        if (amp <= ranges[index]) {
            if (index == 0)
                pers = amp / ranges[index];
            else
                pers = (amp - ranges[index - 1]) / (ranges[index] - ranges[index - 1]);
            break;
        }
    }

    if (index == 0)
        outColor = colors[index];
    else
        outColor = mix(colors[index - 1], colors[index], pers);

    if (reject == 1)
        outColor.a = 0.f;
    else
        outColor.a = alpha;

    //gl_PointSize = 1.;
}
