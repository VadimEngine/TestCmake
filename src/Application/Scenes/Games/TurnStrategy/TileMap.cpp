// class
#include "TileMap.h"

namespace turn_strategy {
    TileMap::TileMap(Texture* texture, SpriteSheet* spriteSheet) {
        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, texture->getId());

        // Get the texture dimensions
        int width, height, channels;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &channels);

        // Determine the number of channels
        if (channels == GL_RGB || channels == GL_SRGB) {
            channels = 3;
        } else if (channels == GL_RGBA || channels == GL_SRGB_ALPHA) {
            channels = 4;
        } else {
            LOG_E("Unsupported texture format: %d", channels);
            glBindTexture(GL_TEXTURE_2D, 0);
            return;
        }

        // Allocate memory to hold the texture data
        size_t dataSize = width * height * channels;
        std::unique_ptr<unsigned char[]> textureData = std::make_unique<unsigned char[]>(dataSize);

        // Retrieve the texture data
        glGetTexImage(GL_TEXTURE_2D, 0, (channels == 3) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureData.get());

        // Resize the tilemap
        mTiles_.resize(height);
        for (auto& row : mTiles_) {
            row.resize(width);
        }

        // iterate texture and do a y flip to handle opengl image flip
        for (int y = 0; y < height; ++y) { // y flip
            for (int x = 0; x < width; ++x) {
                // Calculate the index for accessing the pixel data in the textureData array
                int index = ((height - 1 - y) * width + x) * channels;

                unsigned char* pixel = &textureData[index];

                // Assuming the channels are ordered as RGB
                unsigned char red = pixel[0];
                unsigned char green = pixel[1];
                unsigned char blue = pixel[2];

                // Combine RGB values into a single integer representing the color
                unsigned int combinedColor = (red << 16) | (green << 8) | blue;

                if (combinedColor == 0x0000FF) {
                    // Water
                    mTiles_[y][x].type = Tile::Type::SEA;
                    mTiles_[y][x].sprite = std::make_unique<SpriteSheet::Sprite>(*spriteSheet, glm::ivec2(2, 1));
                } else if (combinedColor == 0x00FF00) {
                    // grass
                    mTiles_[y][x].type = Tile::Type::GRASS;
                    mTiles_[y][x].sprite = std::make_unique<SpriteSheet::Sprite>(*spriteSheet, glm::ivec2(0, 1));
                } else if (combinedColor == 0xFFFF00) {
                    // sand
                    mTiles_[y][x].type = Tile::Type::SAND;
                    mTiles_[y][x].sprite = std::make_unique<SpriteSheet::Sprite>(*spriteSheet, glm::ivec2(3, 1));
                }
            }
        }

        // Unbind the texture
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    TileMap::~TileMap() {}

    void TileMap::render(const Renderer& theRenderer) {
        for (int y = 0; y < mTiles_.size(); ++y) {
            for (int x = 0; x < mTiles_[0].size(); ++x) {
                glm::vec3 position = {x, y, 0};
                glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
                if (mTiles_[y][x].sprite != nullptr) {
                    theRenderer.renderSprite(*(mTiles_[y][x].sprite), translationMatrix, {1,1,1,1});
                }
            }
        }
    }

    const TileMap::Tile* TileMap::tileAt(glm::ivec2 position) const {
        if (mTiles_.size() <= position.y || mTiles_[0].size() <= position.x) {
            return nullptr;
        } else {
            return &mTiles_[position.y][position.x];
        }
    }

    int TileMap::getWidth() const {
        if (mTiles_.empty()) {
            return 0;
        } else {
            return mTiles_[0].size();
        }
    }

    int TileMap::getHeight() const {
        return mTiles_.size();
    }

} // namespace turn_strategy
