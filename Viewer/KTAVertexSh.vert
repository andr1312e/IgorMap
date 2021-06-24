#version 330
in vec4 posAttr;
in float msec;

out VS_OUT {
    vec4 color;
    float radius;
} vs_out;

uniform mat4 mvp;
//uniform float pointSize;
uniform vec4 poiColor;
uniform vec4 voiColor;
uniform vec4 voiRespColor;
uniform float poiRad;
uniform float voiRad;
uniform int current_msec;

void main() {
    int dTime = current_msec - int(msec);
    float dt = float(dTime) / 7000.;
    if (dt > 1)
        dt = 1;
    float dAlpha = 1. - dt;

    float z = posAttr.z - dt;

    gl_Position = mvp * vec4(posAttr.xy, z, 1.0);

    if (posAttr.w < 0.75) {
        vs_out.color = poiColor;
        vs_out.radius = poiRad;

    }
    else if (posAttr.w > 0.75 && posAttr.w < 1.25) {
        vs_out.color = voiColor;
        vs_out.radius = voiRad;
    }
    else if (posAttr.w > 1.25 && posAttr.w < 1.75) {
        vs_out.color = voiRespColor;
        vs_out.radius = voiRad;
    }
    else {
        vec4 gingerColor = voiColor;
        gingerColor.g /= 2;
        vs_out.color = gingerColor;
        vs_out.radius = voiRad;
    }

    /*if (posAttr.z > 6.5) {
        vs_out.color = poiColor;
        vs_out.color.a *= dt;
    }
    else {*/

        if (dAlpha > 1)
            dAlpha = 1;
        /*else if (dAlpha < 0.2)
            dAlpha = 0.2;*/
        vs_out.color.a *= dAlpha;
   //}


    //gl_PointSize = pointSize;
}
