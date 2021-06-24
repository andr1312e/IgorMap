#version 330
in vec4 outColor;
//flat in int reject;

out vec4 color;

void main() {
    /*if (objectColor.a < 0.1) {
        discard;
    }*/
    //if (reject == 1)
    //    discard;
    color = outColor;
}
