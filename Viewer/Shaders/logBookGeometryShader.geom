#version 330
#define PI 3.14159265359
layout( points ) in;
//layout (points, max_vertices = 1) out;
layout( triangle_strip, max_vertices = 4 ) out;

/*in VS_OUT {
   vec4 color;
} gs_in[];
 out vec4 objectColor;*/

uniform float aspect;

void main() {

    //float absCourse = PI / 2.0 - radians(course);
    //objectColor = gs_in[0].color;
    //const int segment = 12;
    //float dAlpha = 2 * PI / float(segment);
    //const float dAz = PI / 2.0;
    //const float radius = 0.0055, rad2 = 0.04;


    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.08,0,0,0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0,0.06,0,0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.08,0.06,0,0);
    EmitVertex();

    EndPrimitive();

    //gl_Position = gl_in[0].gl_Position;
    //gl_PointSize = gl_in[0].gl_PointSize;
    //EmitVertex();
    //EndPrimitive();
}
