#pragma once
// standard lib
#include <filesystem>
#include <vector>
// project
#include "Camera.h"
#include "Renderer.h"
#include "SpriteSheet.h"

namespace turn_strategy {

    class TileMap {
    public:
        /** Struct to hold a tile type and sprite */
        struct Tile{
            /** Types of possible Tiles */
            enum class Type {NONE, SEA, GRASS, SAND};
            /** Tile Type */
            Type type = Type::NONE;
            /** Sprite for this tile */
            std::unique_ptr<SpriteSheet::Sprite> sprite = nullptr;
        };

        /**
         * @brief Construct Tilemap from the given texture and referencing sprites from the
         * spritesheet for each tile
         *
         * @param texture Texture used to position each tile
         * @param spriteSheet sprite sheet that holds sprites for the tiles
         */
        TileMap(Texture* texture, SpriteSheet* spriteSheet);

        /** Destructor */
        ~TileMap();

        /**
         * @brief Render all tiles
         *
         * @param theRenderer Render object
         * @param theCamera
         */
        void render(const Renderer& theRenderer, const Camera& theCamera);

        /**
         * @brief Get reference to tile at the given position if it is in range
         *
         * @param pos tile position
         */
        const Tile* tileAt(glm::ivec2 pos) const;

        /** Get width of tilemap */
        int getWidth() const;

        /** Get height of tilemap */
        int getHeight() const;

    private:
        /** All tiles. [y][x] */
        std::vector<std::vector<Tile>> mTiles_;
    };

} // namespace turn_strategy