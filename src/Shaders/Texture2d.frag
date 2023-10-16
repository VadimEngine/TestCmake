#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D theTexture;

uniform bool uDrawSubImage = false;
uniform vec2 uSpriteGridIndex;
uniform vec2 uSheetSize;
uniform vec2 uSpriteSize;
uniform vec4 uColor = vec4(1.0,1.0,1.0,1.0);

// TODO alpha colors

void main() {
    vec4 texColor;
    if (uDrawSubImage) {
        // TODO maybe always draw a subImage but if want to draw the whole image, set grid to 0,0 and spriteSize to sheetSize
        vec2 spriteStep = uSpriteSize / uSheetSize;

        // Calculate the texture coordinates for the current sprite
        vec2 spriteCoords = spriteStep * uSpriteGridIndex +  vec2(TexCoord.x, 1-TexCoord.y) / (uSheetSize / uSpriteSize);

        texColor = texture(theTexture, vec2(spriteCoords.x, spriteCoords.y));
    } else {
        texColor = texture(theTexture, vec2(TexCoord.x, 1- TexCoord.y));
    }

    if (texColor.rgb == vec3(1.0, 0.0, 1.0) || texColor.rgb == vec3(0.8, 0.0, 0.8)) {
        discard; // Discard fragment if spritesheet background color
    }

    FragColor = texColor * uColor;
}