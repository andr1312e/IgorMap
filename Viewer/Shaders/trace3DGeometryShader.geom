#version 330
#define PI 3.14159265359
layout( points ) in;
//layout( line_strip, max_vertices = 20 ) out;
layout( triangle_strip, max_vertices = 24 ) out;

in gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
} gl_in[];

uniform float aspect;
//uniform float course;

void main() {

    //float absCourse = PI / 2.0 - radians(course);
    //objectColor = gs_in[0].color;
//    const int segment = 12;
//    float dAlpha = 2 * PI / float(segment);
    //const float dAz = PI / 2.0;
    const float radius = 6., rad2 = 0.04;

    /*for (int i = 0; i < segment + 1; i++) {
        gl_Position = gl_in[0].gl_Position +
                vec4(radius * cos(dAlpha * i) / aspect,
                radius * sin(dAlpha * i),
                0.0, 0.0);
        EmitVertex();
    }
    EndPrimitive();*/

    float dAlpha = PI / 6.0;
    const float dAz = PI / 2.0;
    for(int i = 0; i < 12;) {

        gl_Position = gl_in[0].gl_Position +
            vec4(radius * cos(dAz - dAlpha * i) / aspect,
                radius * sin(dAz - dAlpha * i),
                 0.0, 0.0);
        EmitVertex();
        i++;

        gl_Position = gl_in[0].gl_Position;
        EmitVertex();

        gl_Position = gl_in[0].gl_Position +
            vec4(radius * cos(dAz - dAlpha * i) / aspect,
                radius * sin(dAz - dAlpha * i),
                 0.0, 0.0);
        EmitVertex();
        i++;

        gl_Position = gl_in[0].gl_Position +
            vec4(radius * cos(dAz - dAlpha * i) / aspect,
                radius * sin(dAz - dAlpha * i),
                 0.0, 0.0);
        EmitVertex();

        EndPrimitive();
    }

    /*vec4 glPos = gl_in[0].gl_Position;

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = vec4(gl_in[0].gl_Position.x,
                       gl_in[0].gl_Position.y,
                       0.1,
                       gl_in[0].gl_Position.w);
    EmitVertex();

    EndPrimitive();

    float alpha = atan(glPos.y, glPos.x);
    float maxDist = 300;*/

    /*gl_Position = glPos;
    EmitVertex();

    gl_Position = vec4(maxDist * cos(alpha),
                       maxDist * sin(alpha), glPos.z, glPos.w);
    EmitVertex();

    EndPrimitive();*/

    /*gl_Position = gl_in[0].gl_Position +
            vec4(radius * cos(absCourse) / aspect,
            radius * sin(absCourse),
            0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position +
            vec4(rad2 * cos(absCourse) / aspect,
            rad2 * sin(absCourse),
            0.0, 0.0);
    EmitVertex();

    EndPrimitive();*/

}
