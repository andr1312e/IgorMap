#version 330
#define PI 3.14159265359
layout( lines ) in;
//layout (points, max_vertices = 1) out;
layout( line_strip, max_vertices = 20 ) out;

/*in VS_OUT {
   vec4 color;
} gs_in[];
 out vec4 objectColor;*/

uniform float aspect;
uniform float course;
uniform int edge;

void main() {

    float absCourse = PI / 2.0 - radians(course);
    //objectColor = gs_in[0].color;
    const int segment = 12;
    float dAlpha = 2 * PI / float(segment);
    //const float dAz = PI / 2.0;
    const float radius = 0.0055, rad2 = 0.04;

    for (int i = 0; i < segment + 1; i++) {
        gl_Position = gl_in[0].gl_Position +
                vec4(radius * cos(dAlpha * i) / aspect,
                radius * sin(dAlpha * i),
                0.0, 0.0);
        EmitVertex();
    }
    EndPrimitive();

    gl_Position = gl_in[0].gl_Position +
            vec4(radius * cos(absCourse) / aspect,
            radius * sin(absCourse),
            0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position +
            vec4(rad2 * cos(absCourse) / aspect,
            rad2 * sin(absCourse),
            0.0, 0.0);
    EmitVertex();

    EndPrimitive();

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    EndPrimitive();

    const float lineLength = 0.05;

    if (edge == 0) {
        gl_Position = gl_in[1].gl_Position + vec4(lineLength/aspect, 0,0,0);
        EmitVertex();

        gl_Position = gl_in[1].gl_Position;
        EmitVertex();

        gl_Position = gl_in[1].gl_Position + vec4(0, lineLength,0,0);
        EmitVertex();

        EndPrimitive();
    }
    else if (edge == 1) {
        gl_Position = gl_in[1].gl_Position + vec4(lineLength/aspect, 0,0,0);
        EmitVertex();

        gl_Position = gl_in[1].gl_Position;
        EmitVertex();

        gl_Position = gl_in[1].gl_Position + vec4(0, -lineLength,0,0);
        EmitVertex();

        EndPrimitive();
    }
    else if (edge == 2) {
        gl_Position = gl_in[1].gl_Position + vec4(-lineLength/aspect, 0,0,0);
        EmitVertex();

        gl_Position = gl_in[1].gl_Position;
        EmitVertex();

        gl_Position = gl_in[1].gl_Position + vec4(0, -lineLength,0,0);
        EmitVertex();

        EndPrimitive();
    }
    else if (edge == 3) {
        gl_Position = gl_in[1].gl_Position + vec4(-lineLength/aspect, 0,0,0);
        EmitVertex();

        gl_Position = gl_in[1].gl_Position;
        EmitVertex();

        gl_Position = gl_in[1].gl_Position + vec4(0, lineLength,0,0);
        EmitVertex();

        EndPrimitive();
    }

    //gl_Position = gl_in[0].gl_Position;
    //gl_PointSize = gl_in[0].gl_PointSize;
    //EmitVertex();
    //EndPrimitive();
}
