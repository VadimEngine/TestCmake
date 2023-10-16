#pragma once
#include <glm/vec2.hpp>

class SpriteSheet {
public:
    struct Sprite {
        /** The sprite sheet this sprite is from */
        SpriteSheet* parentSpriteSheet = nullptr;
        /** The grid this sprite is on the Sprite Sheet */
        glm::ivec2 gridIndex;
        /** The size of this sprite. Can be used to draw a sprite consisting of multiple grids */
        glm::ivec2 spriteSize;

        /**
         * Constructor
         * \param theSpriteSheet Parent Sprites Sheet
         * \param theGridIndex Grid index of the Sprite Sheet
         * \param theSpriteSize Size of the sprite
         */
        Sprite(SpriteSheet* theSpriteSheet, glm::ivec2 theGridIndex, glm::ivec2 theSpriteSize);

        /**
         * Constructor. Sets spriteSize to be the parent SpriteSheet default sprite size
         * \param theSpriteSheet Parent Sprites Sheet
         * \param theGridIndex Grid index of the Sprite Sheet
         */
        Sprite(SpriteSheet* theSpriteSheet, glm::ivec2 theGridIndex);
    };
private:
    /** Texture Id*/
    unsigned int mTextureId_;
    /** Sprite sheet size in pixels*/
    glm::ivec2 mSheetSize_;
    /** Default sprite size for this sheet. (Used to calculates the grid locations)*/
    glm::ivec2 mDefaultSpriteSize_;

public:
    /**
     * Constructor
     * \param textureId Texture id for this sprite sheet
     * \param sheetSize Sprite sheet size in pixels
     * \param defaultSpiteSize Parent Sprites Sheet
     */
    SpriteSheet(unsigned int textureId, glm::ivec2 sheetSize, glm::ivec2 defaultSpiteSize);
    
    /** Destructor */
    ~SpriteSheet();
    
    /** Get Texture Id*/
    unsigned int getTextureId();

    /** Get Sprite sheet size in pixels */
    glm::ivec2 getSheetSize();

    /** Get the default sprite size for this Sprite Sheet */
    glm::ivec2 getDefaultSpriteSize();
};