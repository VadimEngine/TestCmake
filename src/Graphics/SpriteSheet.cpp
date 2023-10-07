#include "SpriteSheet.h"

SpriteSheet::Sprite::Sprite(SpriteSheet* theSpriteSheet, glm::ivec2 theGridIndex, glm::ivec2 theSpriteSize)
    : parentSpriteSheet(theSpriteSheet), gridIndex(theGridIndex), spriteSize(theSpriteSize) {}

SpriteSheet::Sprite::Sprite(SpriteSheet* theSpriteSheet, glm::ivec2 theGridIndex) 
    : parentSpriteSheet(theSpriteSheet), gridIndex(theGridIndex), spriteSize(parentSpriteSheet->getDefaultSpriteSize()) {

}

SpriteSheet::SpriteSheet(unsigned int textureId, glm::ivec2 sheetSize, glm::ivec2 defaultSpiteSize) 
    : mTextureId_(textureId), mSheetSize_(sheetSize), mDefaultSpriteSize_(defaultSpiteSize) {}

unsigned int SpriteSheet::getTextureId() {
    return mTextureId_;
}

glm::ivec2 SpriteSheet::getSheetSize() {
    return mSheetSize_;
}

glm::ivec2 SpriteSheet::getDefaultSpriteSize() {
    return mDefaultSpriteSize_;
}
