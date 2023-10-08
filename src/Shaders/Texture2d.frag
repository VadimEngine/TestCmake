#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform bool uDrawSubImage = false;
uniform vec2 uSpriteGridIndex;
uniform vec2 uSheetSize;
uniform vec2 uSpriteSize;// = vec2(16,16);

// TODO alpha colors

void main() {

    if (uDrawSubImage) {
        // TODO maybe always draw a subImage but if want to draw the whole image, set grid to 0,0 and spriteSize to sheetSize
        vec2 spriteStep = uSpriteSize / uSheetSize;

        // Calculate the texture coordinates for the current sprite
        vec2 spriteCoords = spriteStep * uSpriteGridIndex +  vec2(TexCoord.x, 1-TexCoord.y) / (uSheetSize / uSpriteSize);

        FragColor = texture(texture0, vec2(spriteCoords.x, spriteCoords.y));
    } else {
        FragColor = texture(texture0, vec2(TexCoord.x, 1- TexCoord.y));
    }
}
