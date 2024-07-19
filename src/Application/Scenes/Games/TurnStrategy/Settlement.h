#pragma once
#include "SpriteSheet.h"
#include "SpriteRenderable.h"
#include "Camera.h"
#include "Entity.h"
#include <string>
#include <unordered_set>
#include "ModelRenderable.h"
#include "TextRenderable.h"
#include <vector>
#include "Utils.h"

namespace turn_strategy {

    // forward declare TurnStrategyGame
    class TurnStrategyGame;

    class Settlement : public Entity {
    public:
        Settlement(TurnStrategyGame& theGame, SpriteSheet::Sprite* pSprite, glm::ivec2 tilePosition);

        /**
         * Update Unit
         * @param dt Time since last update
         */
        void update(const float dt) override;

        void render(const Renderer& theRenderer, const Camera& theCamera) const override;

        void setName(const std::string& newName);

        std::string getName() const;

        void addTerritory(glm::ivec2 tilePosition);

        void resetForTurn();

        int getSize() const;

        int getPopulation() const;

        void setPopulation(int newPopulation);

        bool canSpawnUnit();

    private:
        /** Map of territory tiles */
        std::unordered_set<glm::ivec2, utils::Vec2Hash> territoryTiles;
        /** Settlement name */
        std::string mName_;
        /** Settlement size that grows ever few turns */
        int population = 1;
        /** how many tiles this settlement has (proportionate to population) */
        int size = 1;
        /** Renderable to shade in territory tiles */
        ModelRenderable borderRenderable;
        /** Reference to the Label Text renderable */
        TextRenderable* mLabelTextRenderable_ = nullptr;
        /** Game this Settlement is in */
        TurnStrategyGame& mGame_;
    };
} // namespace turn_strategy