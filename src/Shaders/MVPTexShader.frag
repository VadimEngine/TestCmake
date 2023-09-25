#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
    // 1 - y for texCord to flip image
    FragColor = mix(texture(texture0, vec2(TexCoord.x, 1-TexCoord.y)), texture(texture1, vec2(TexCoord.x, 1-TexCoord.y)), 0.2);
}
