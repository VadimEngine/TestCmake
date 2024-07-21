// forward declare
#include "App.h"
#include "Scene.h"
#include "TurnStrategyGame.h"
#include "TurnStrategyScene.h"
// class
#include "Settlement.h"

namespace turn_strategy {
    Settlement::Settlement(TurnStrategyGame& theGame, SpriteSheet::Sprite* pSprite, glm::ivec2 tilePosition)
     : Entity(theGame.getScene()), mGame_(theGame) {
        addRenderable(new SpriteRenderable(pSprite));
        territoryTiles.insert(tilePosition);

        borderRenderable.setModel(mScene_.getResources().getResource<Model>("RectPlane"));
        borderRenderable.setShader(mScene_.getApp().getResources().getResource<Shader>("Assimp"));
        borderRenderable.setColor({1,0, 0,.5f});

        ModelRenderable* labelRectRenderable = new ModelRenderable(
            mScene_.getResources().getResource<Model>("RectPlane"),
            mScene_.getApp().getResources().getResource<Shader>("Assimp")
        );
        labelRectRenderable->setScale({1.f, .5f, 1});
        labelRectRenderable->setColor({.3f, .3f, .3f, 1.f});
        labelRectRenderable->setPosition({0, -.75f, 0});
        addRenderable(labelRectRenderable);

        mLabelTextRenderable_ = new TextRenderable(
            mName_,
            mScene_.getApp().getResources().getResource<Font>("Consolas")
        );
        mLabelTextRenderable_->setPosition({0, -.75f, 0});
        mLabelTextRenderable_->setScale({.07f, .07f, 1});
        addRenderable(mLabelTextRenderable_);
    }

    void Settlement::update(const float dt) {}

    void Settlement::render(const Renderer& theRenderer, const Camera& theCamera) const {
        // Draw Settlement
        Entity::render(theRenderer, theCamera);

        // draw border
        std::array<glm::ivec2, 4> dirs = {{
           {1,0},
           {0,1},
           {0,-1},
           {-1,0}
        }};

        glm::vec4 lineColor = {1,0,0,1};
        glm::mat4 translationMatrix = glm::identity<glm::mat4>();

        for (const auto& eachTile : territoryTiles) {
            borderRenderable.render(theRenderer, theCamera, glm::translate(glm::mat4(1.0f), {eachTile.x, eachTile.y, 0.f}));
        }
    }

    void Settlement::setName(const std::string& newName) {
        mName_ = newName;
        mLabelTextRenderable_->setText(newName);
    }

    std::string Settlement::getName() const {
        return mName_;
    }

    void Settlement::addTerritory(glm::ivec2 tilePosition) {
        territoryTiles.insert(tilePosition);
        ++size;
    }

    void Settlement::resetForTurn() {
        // increase population every turn
        ++population;
    }

    int Settlement::getSize() const {
        return size;
    }

    int Settlement::getPopulation() const {
        return population;
    }

    void Settlement::setPopulation(int newPopulation) {
        population = newPopulation;
    }

    bool Settlement::canSpawnUnit() const {
        // check if a unit in on this settlement
        for (const auto& eachUnit: mGame_.getUnitList()) {
            if (eachUnit->getPosition().x == mPosition_.x && eachUnit->getPosition().y == getPosition().y) {
                return false;
            }
        }
        // check if enough population
        return population > 1;
    }

} // namespace turn_strategy