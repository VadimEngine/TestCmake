#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
// TODO name this uniforms with "u" Prefix
uniform bool wireframeMode = false;
uniform vec4 wireframeColor = vec4(0,0,0,1.0);
uniform vec4 uColor = vec4(1.0,1.0,1.0,1.0);

void main() {
    if (wireframeMode) {
        FragColor = wireframeColor;
    } else {
        FragColor = uColor;
        //FragColor = texture(texture_diffuse1, TexCoords);
    }
}