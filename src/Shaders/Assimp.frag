#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform bool uWireframeMode = false;
uniform vec4 uWireframeColor = vec4(0,0,0,1.0);
uniform vec4 uColor = vec4(1.0,1.0,1.0,1.0);

void main() {
    if (uWireframeMode) {
        FragColor = uWireframeColor;
    } else {
        FragColor = uColor;
        //FragColor = texture(texture_diffuse1, TexCoords);
    }
}