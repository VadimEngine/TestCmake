#pragma once
#include "SpriteSheet.h"
#include "SpriteRenderable.h"
#include "Camera.h"
#include "Entity.h"
#include <string>
#include <unordered_set>
#include "ModelRenderable.h"
#include <vector>


namespace TurnStrategy {

    // forward declare TurnStrategyGame
    class TurnStrategyGame;

    class Settlement : public Entity {
    private:
        /** Hash for glm::ivec2 */
        struct Vec2Hash {
            size_t operator()(const glm::ivec2& v) const {
                return std::hash<int>()(v.x) ^ std::hash<int>()(v.y);
            }
        };

        std::vector<int> test;
        std::string mName_;

        // natural settlement size that grows ever few turns
        int population = 1;
        // how many tiles this settlement has (proportionate to population)
        int size = 1;

        Model mRectModel_;
        ModelRenderable* borderRenderable;
        ModelRenderable* labelRectRenderable;

        TurnStrategyGame& mGame_;


    public:

        std::unordered_set<glm::ivec2, Vec2Hash> territoryTiles;

        Settlement(TurnStrategyGame& theGame, SpriteSheet::Sprite* pSprite, glm::ivec2 tilePosition);


        /** 
         * Update Unit
         * \param dt Time since last update
         */
        void update(const float dt) override;

        void render(const Renderer& theRenderer, const Camera& theCamera) const override;

        void setName(const std::string& newName);

        std::string getName();

        void addTerritory(glm::ivec2 tilePosition);

        void resetForTurn();

        int getSize();

        int getPopulation();

        void setPopulation(int newPopulation);

        bool canSpawnUnit();

    };
} // namespace TurnStrategy