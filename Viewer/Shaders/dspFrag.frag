#version 330 core
in vec4 ourColor;

//noperspective in vec3 GEdgeDistance;

out vec4 FragColor;

void main() {
    float lineWidth = 1.f;
    vec4 lineColor = vec4(1.f,1.f,1.f,1.f);

    // Find the smallest distance
    /*float d = min( GEdgeDistance.x, GEdgeDistance.y );
    d = min( d, GEdgeDistance.z );

    float mixVal;
    if( d < lineWidth - 1 ) {
        mixVal = 1.0;
    } else if( d > lineWidth + 1 ) {
        mixVal = 0.0;
    } else {
        float x = d - (lineWidth - 1);
        mixVal = exp2(-2.0 * (x*x));
    }
    FragColor = mix( ourColor, lineColor, mixVal );*/
    FragColor = ourColor;
}
