#pragma once
// standard lib
#include <queue>
#include <string>
#include <unordered_set>
// project
#include "Entity.h"
#include "SpriteSheet.h"
#include "SpriteRenderable.h"
#include "Utils.h"

namespace turn_strategy {
    // forward declare TurnStrategyGame
    class TurnStrategyGame;

    class Unit : public Entity {
    public:

        /**
         * @brief Construct a new Unit object
         *
         * @param theGame the game this unit is in
         * @param pSprite Sprite for this unit
         */
        Unit(TurnStrategyGame& theGame,SpriteSheet::Sprite* pSprite);

        /**
         * Update Unit
         * @param dt Time since last update
         */
        void update(const float dt) override;

        /**
         * @brief Update the name of this Unit
         *
         * @param newName New Name
         */
        void setName(const std::string& newName);

        /**
         * @brief Get name of this Unit
         */
        std::string getName() const;

        /**
         * @brief Get how many available moves this unit has for this turn
         */
        int getMoves() const;

        /**
         * @brief Highlight the tiles this unit can move to
         *
         * @param theRenderer Renderer object
         */
        void renderValidMoves(const Renderer& theRenderer);

        /**
         * @brief Move the unit to a tile and use decrease moves proportionally
         *
         * @param newPosition
         */
        void moveToTile(glm::ivec2 newPosition);

        /**
         * @brief Decrease the moves for this unit with the action cost
         *
         * @param cost cost of the action
         */
        void doAction(int cost);

        /**
         * @brief Reset this unit for the next turn
         */
        void resetForTurn();

        /**
         * @brief If this unit can make a settlement based on available actions and other nearby settlements
         */
        bool canSettle() const;

    private:
        /**
         * @brief Helper method to get the tiles this unit can move to
         *
         * @return std::unordered_set<glm::ivec2, utils::Vec2Hash>
         */
        std::unordered_set<glm::ivec2, utils::Vec2Hash> getMoveableTiles() const;

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