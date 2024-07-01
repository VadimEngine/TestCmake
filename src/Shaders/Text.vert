#version 330 core
layout (location = 0) in vec4 vertex;
out vec2 TexCoords;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}