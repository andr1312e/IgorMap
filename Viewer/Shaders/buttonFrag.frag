#version 330
out vec4 color;

uniform vec4 ourColor;
uniform int selectedItem;
uniform int hoveredItem;

flat in int itemNumber;

void main() {
    if (itemNumber == selectedItem) {
        color = vec4(ourColor.r + 0.2,
                     ourColor.g + 0.2,
                     ourColor.b + 0.2,
                     ourColor.a);
    }
    else if (itemNumber == hoveredItem) {
        color = vec4(ourColor.r + 0.1,
                     ourColor.g + 0.1,
                     ourColor.b + 0.1,
                     ourColor.a);
    }
    else {
        color = ourColor;
    }
}
