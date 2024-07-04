#pragma once
#include "SpriteSheet.h"
#include "SpriteRenderable.h"
#include "Camera.h"
#include "Entity.h"
#include <string>
#include <unordered_set>
#include <queue>
#include "Utils.h"

namespace turn_strategy {

    // forward declare TurnStrategyGame
    class TurnStrategyGame;

    class Unit : public Entity {
    private:

        std::string mName_;

        int maxMoves = 5;
        int moves = maxMoves;

        TurnStrategyGame& mGame_;


    public:
        Unit(Scene& scene, TurnStrategyGame& theGame,SpriteSheet::Sprite* pSprite);

        /**
         * Update Unit
         * @param dt Time since last update
         */
        void update(const float dt) override;

        void setName(const std::string& newName);

        std::string getName();

        int getMoves();

        void renderValidMoves(const Renderer& theRenderer, const Camera& theCamera);

        std::unordered_set<glm::ivec2, utils::Vec2Hash> getMoveableTiles();

        void moveToTile(glm::ivec2 newPosition);

        void doAction(int cost);

        void resetForTurn();

        bool canSettle();

    };
} // namespace turn_strategy