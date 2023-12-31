#pragma once
#include "SpriteSheet.h"
#include "SpriteRenderable.h"
#include "Camera.h"
#include "Entity.h"
#include <string>
#include <unordered_set>
#include <queue>

namespace TurnStrategy {

// forward declare TurnStrategyGame
class TurnStrategyGame;

    class Unit : public Entity {
    public:
        struct Vec2Hash {
            size_t operator()(const glm::ivec2& v) const {
                // Custom hash function for glm::ivec2
                return std::hash<int>()(v.x) ^ std::hash<int>()(v.y);
            }
        };
    private:

        std::string mName_;

        int maxMoves = 5;
        int moves = maxMoves;

        TurnStrategyGame& mGame_;


    public:
        Unit(TurnStrategyGame& theGame,SpriteSheet::Sprite* pSprite);

        /** 
         * Update Unit
         * \param dt Time since last update
         */
        void update(const float dt) override;

        void setName(const std::string& newName);

        std::string getName();

        int getMoves();

        void renderValidMoves(const Renderer& theRenderer, const Camera& theCamera);

        std::unordered_set<glm::ivec2, Vec2Hash> getMoveableTiles();

        void moveToTile(glm::ivec2 newPosition);

        void doAction(int cost);

        void resetForTurn();

        bool canSettle();

    };
} // namespace TurnStrategy