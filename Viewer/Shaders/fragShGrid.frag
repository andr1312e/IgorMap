#version 330
//in vec4 ourColor;
out vec4 color;

//uniform bool isColorDependenceOnY;
uniform vec4 objectColor;

void main() {
    /*if (isColorDependenceOnY) {
        color = ourColor;
    }
    else*/
        color = objectColor;
}
