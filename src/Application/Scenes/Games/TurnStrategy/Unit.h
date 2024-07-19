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
    public:
        Unit(Scene& scene, TurnStrategyGame& theGame,SpriteSheet::Sprite* pSprite);

        /**
         * Update Unit
         * @param dt Time since last update
         */
        void update(const float dt) override;

        void setName(const std::string& newName);

        std::string getName() const;

        int getMoves() const;

        void renderValidMoves(const Renderer& theRenderer, const Camera& theCamera);

        std::unordered_set<glm::ivec2, utils::Vec2Hash> getMoveableTiles() const;

        void moveToTile(glm::ivec2 newPosition);

        void doAction(int cost);

        void resetForTurn();

        bool canSettle() const;

    private:
        /** Name of this Unit */
        std::string mName_;
        /** Max moves per turn */
        int mMaxMoves_ = 5;
        /** Remaining moves for this turn*/
        int mMoves_ = mMaxMoves_;
        /** Game this unit is in */
        TurnStrategyGame& mGame_;
    };
} // namespace turn_strategy