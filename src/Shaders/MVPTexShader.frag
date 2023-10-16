#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform bool wireframeMode = false;
uniform vec4 wireframeColor = vec4(0,0,0,1.0);
uniform vec4 uColor = vec4(1.0,1.0,1.0,1.0);

void main() {
    if (wireframeMode) {
        FragColor = wireframeColor;
    } else {
        // 1 - y for texCord to flip image
        FragColor = mix(texture(texture0, vec2(TexCoord.x, 1-TexCoord.y)), texture(texture1, vec2(TexCoord.x, 1-TexCoord.y)), 0.2) * uColor;
    }
}
