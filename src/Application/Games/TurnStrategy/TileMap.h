#pragma once
#include "SpriteSheet.h"
#include "Renderer.h"
#include "Camera.h"
#include <vector>
#include <filesystem>

namespace TurnStrategy {

    class TileMap {
    public:
        struct Tile{
            enum class Type {NONE, SEA, GRASS, SAND};

            Type type = Type::NONE;

            SpriteSheet::Sprite* sprite = nullptr;
        };

        const int rows = 20;
        const int cols = 20;

        SpriteSheet mSpriteSheet_;


        // Create a 2D vector of Tile objects
        std::vector<std::vector<Tile>> tiles;

        TileMap();

        TileMap(const std::string& tileMapPath);

        ~TileMap();

        void render(const Renderer& theRenderer, const Camera& theCamera);

    };

} // namespace TurnStrategy