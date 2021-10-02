#version 330
in vec3 posAttr;
uniform mat4 mvp;
uniform float zcoord;

/*out VS_OUT {
    float course;
} vs_out;*/

void main() {
    gl_Position = mvp * vec4(posAttr.xy, zcoord, 1.0);

    //vs_out.course = posAttr.z;
}
