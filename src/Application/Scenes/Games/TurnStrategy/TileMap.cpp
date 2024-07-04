#include "TileMap.h"

namespace turn_strategy {

    TileMap::TileMap(Texture* texture, SpriteSheet* spriteSheet)
    : tiles(rows, std::vector<Tile>(cols)) {
        // Bind the texture
        glBindTexture(GL_TEXTURE_2D, texture->getId());

        // Get the texture dimensions
        int width, height, channels;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &channels);

        // Determine the number of channels
        if (channels == GL_RGB) {
            channels = 3;
        } else if (channels == GL_RGBA) {
            channels = 4;
        } else {
            LOG_E("Unsupported texture format: %d", channels);
            glBindTexture(GL_TEXTURE_2D, 0);
            return;
        }

        // Allocate memory to hold the texture data
        size_t dataSize = width * height * channels;
        unsigned char* textureData = new unsigned char[dataSize];

        // Retrieve the texture data
        glGetTexImage(GL_TEXTURE_2D, 0, (channels == 3) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureData);


        // iterate texture
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // Calculate the index for accessing the pixel data in the textureData array
                int index = (y * width + x) * channels;

                unsigned char* pixel = &textureData[index];

                // Assuming the channels are ordered as RGB
                unsigned char red = pixel[0];
                unsigned char green = pixel[1];
                unsigned char blue = pixel[2];

                // Combine RGB values into a single integer representing the color
                unsigned int combinedColor = (red << 16) | (green << 8) | blue;

                if (combinedColor == 0x0000FF) {
                    // Water
                    tiles[y][x].type = Tile::Type::SEA;
                    tiles[y][x].sprite = new SpriteSheet::Sprite(*spriteSheet, glm::ivec2(2, 1));
                } else if (combinedColor == 0x00FF00) {
                    // grass
                    tiles[y][x].type = Tile::Type::GRASS;
                    tiles[y][x].sprite = new SpriteSheet::Sprite(*spriteSheet, glm::ivec2(0, 1));
                } else if (combinedColor == 0xFFFF00) {
                    // sand
                    tiles[y][x].type = Tile::Type::SAND;
                    tiles[y][x].sprite = new SpriteSheet::Sprite(*spriteSheet, glm::ivec2(3, 1));
                }
            }
        }
        // Free the allocated memory
        delete[] textureData;

        // Unbind the texture
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    TileMap::~TileMap() {}

    void TileMap::render(const Renderer& theRenderer, const Camera& theCamera) {
        for (int i = 0; i < tiles.size(); i++) {
            for (int j = 0; j < tiles[0].size(); j++) {
                glm::vec3 position = {i, j, 0};
                glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
                if (tiles[i][j].sprite != nullptr) {
                    theRenderer.renderSprite(*(tiles[i][j].sprite), theCamera, translationMatrix, {1,1,1,1});
                }
            }
        }
    }

} // namespace turn_strategy
