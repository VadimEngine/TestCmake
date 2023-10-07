#pragma once
#include <glm/vec2.hpp>

class SpriteSheet {
public:
    struct Sprite {
        SpriteSheet* parentSpriteSheet = nullptr;
        glm::ivec2 gridIndex;
        glm::ivec2 spriteSize; // default to size from spritesheet
        // If the sprite consists of multiple sprites
        // maybe store the sprite sheet size here, then we dont need multiple sprites
        // property, just treat the sprite sheet as bigger size if needed

        Sprite(SpriteSheet* theSpriteSheet, glm::ivec2 theGridIndex, glm::ivec2 theSpriteSize);
        Sprite(SpriteSheet* theSpriteSheet, glm::ivec2 theGridIndex);

    };
private:
    unsigned int mTextureId_;

    glm::ivec2 mSheetSize_;

    glm::ivec2 mDefaultSpriteSize_;

public:
    SpriteSheet(unsigned int textureId, glm::ivec2 sheetSize, glm::ivec2 defaultSpiteSize);

    unsigned int getTextureId();

    glm::ivec2 getSheetSize();

    glm::ivec2 getDefaultSpriteSize();

};