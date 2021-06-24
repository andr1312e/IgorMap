#version 330

uniform vec4 objectColor;

out vec4 color;

void main() {
    /*if (objectColor.a < 0.1) {
        discard;
    }*/
    //if (reject == 1)
    //    discard;
    color = objectColor;
}
