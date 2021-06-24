#version 330
#define PI 3.14159265359
layout( points ) in;
//layout (points, max_vertices = 1) out;
layout( triangle_strip, max_vertices = 24 ) out;

in VS_OUT {
   vec4 color;
   float radius;
} gs_in[];
 out vec4 objectColor;

//uniform float radius;
uniform float aspect;

void main() {
    objectColor = gs_in[0].color;

    float dAlpha = PI / 6.0;
    const float dAz = PI / 2.0;
    for(int i = 0; i < 12;) {

        gl_Position = gl_in[0].gl_Position +
            vec4(gs_in[0].radius * cos(dAz - dAlpha * i) / aspect,
                gs_in[0].radius * sin(dAz - dAlpha * i),
                 0.0, 0.0);
        EmitVertex();
        i++;

        gl_Position = gl_in[0].gl_Position;
        EmitVertex();

        gl_Position = gl_in[0].gl_Position +
            vec4(gs_in[0].radius * cos(dAz - dAlpha * i) / aspect,
                gs_in[0].radius * sin(dAz - dAlpha * i),
                 0.0, 0.0);
        EmitVertex();
        i++;

        gl_Position = gl_in[0].gl_Position +
            vec4(gs_in[0].radius * cos(dAz - dAlpha * i) / aspect,
                gs_in[0].radius * sin(dAz - dAlpha * i),
                 0.0, 0.0);
        EmitVertex();

        EndPrimitive();
    }

    //gl_Position = gl_in[0].gl_Position;
    //gl_PointSize = gl_in[0].gl_PointSize;
    //EmitVertex();
    //EndPrimitive();
}
