#include "TileMap.h"

namespace TurnStrategy {

    TileMap::TileMap()
    :mSpriteSheet_(Texture::getLoadedTexture("SpriteSheet").value(), {512, 512}, {16,16}),
    tiles(rows, std::vector<Tile>(cols))  {
        for (int i = 0; i < tiles.size(); i++) {
            for (int j = 0; j < tiles[0].size(); j++) {
                tiles[i][j].sprite = new SpriteSheet::Sprite(&mSpriteSheet_, glm::ivec2(0, 1));
            }
        }
    }

    TileMap::TileMap(const std::string& tileMapPath)  
    :mSpriteSheet_(Texture::getLoadedTexture("SpriteSheet").value(), {512, 512}, {16,16}),
    tiles(rows, std::vector<Tile>(cols)) {
        // res/World1.png
        int width, height;
        int channels;
        // Load image file
        unsigned char* textureData = SOIL_load_image(tileMapPath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

        if (textureData == nullptr) {
            LOG_E("Tilemap not found: %s", tileMapPath.c_str());
            const char* errorMessage = SOIL_last_result();
            if (errorMessage != nullptr) {
                LOG_E("SOIL error:: %s", errorMessage);
            }
        }

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
                    tiles[y][x].sprite = new SpriteSheet::Sprite(&mSpriteSheet_, glm::ivec2(2, 1));
                } else if (combinedColor == 0x00FF00) {
                    // grass
                    tiles[y][x].type = Tile::Type::GRASS;
                    tiles[y][x].sprite = new SpriteSheet::Sprite(&mSpriteSheet_, glm::ivec2(0, 1));
                } else if (combinedColor == 0xFFFF00) {
                    // sand
                    tiles[y][x].type = Tile::Type::SAND;
                    tiles[y][x].sprite = new SpriteSheet::Sprite(&mSpriteSheet_, glm::ivec2(3, 1));
                }
            }
        }
        SOIL_free_image_data(textureData);
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

} // namespace TurnStrategy
