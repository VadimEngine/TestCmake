#include "Settlement.h"
#include "TurnStrategyGame.h"
#include "Scene.h"
#include "App.h"

namespace turn_strategy {

    Settlement::Settlement(Scene& scene, TurnStrategyGame& theGame, SpriteSheet::Sprite* pSprite, glm::ivec2 tilePosition)
     : Entity(scene), mGame_(theGame) {
        addRenderable(new SpriteRenderable(pSprite));
        territoryTiles.insert(tilePosition);
        mRectModel_.addSharedMesh(mScene_.getApp().getResources().getResource<Mesh>("RectPlane"));
        borderRenderable = new ModelRenderable(&mRectModel_, mScene_.getApp().getResources().getResource<Shader>("Assimp"));
        borderRenderable->setColor({1,0, 0,.5f});

        labelRectRenderable = new ModelRenderable(&mRectModel_, mScene_.getApp().getResources().getResource<Shader>("Assimp"));
        labelRectRenderable->setScale({1.f, .5f, 1});
        labelRectRenderable->setColor({.3f, .3f, .3f, 1.f});
    }

    void Settlement::update(const float dt) {
    }

    void Settlement::render(const Renderer& theRenderer, const Camera& theCamera) const {
        // Draw Settlement
        Entity::render(theRenderer, theCamera);

        // draw settlement label
        {
            glm::mat4 translationMatrix2 = glm::translate(glm::mat4(1.0f), {mPosition_.x, mPosition_.y-.75, mPosition_.z});
            labelRectRenderable->render(theRenderer, theCamera, translationMatrix2);
            // TODO remove this temp cast
            const_cast<Renderer&>(theRenderer).renderTextNormalized(
                mName_,
                translationMatrix2,
                theCamera,
                *(mScene_.getApp().getResources().getResource<Font>("Consolas")),
                .005f,
                {1,1,1}
            );
        }
        std::vector<glm::ivec2> dirs = {
            {1,0},
            {0,1},
            {0,-1},
            {-1,0},
        };

        glm::vec4 lineColor = {1,0,0,1};
        glm::mat4 translationMatrix = glm::identity<glm::mat4>();

        // draw border
        for (const auto& eachTile : territoryTiles) {
            borderRenderable->render(theRenderer, theCamera, glm::translate(glm::mat4(1.0f), {eachTile.x, eachTile.y, 0.f}));
        }
    }

    void Settlement::setName(const std::string& newName) {
        mName_ = newName;
    }

    std::string Settlement::getName() {
        return mName_;
    }

    void Settlement::addTerritory(glm::ivec2 tilePosition) {
        territoryTiles.insert(tilePosition);
        size++;
    }

    void Settlement::resetForTurn() {
        // increase population every turn
        population++;
    }

    int Settlement::getSize() {
        return size;
    }

    int Settlement::getPopulation() {
        return population;
    }

    void Settlement::setPopulation(int newPopulation) {
        population = newPopulation;
    }

    bool Settlement::canSpawnUnit() {
        for (auto& eachUnit: mGame_.getUnitList()) {
            if (eachUnit->getPosition().x == mPosition_.x && eachUnit->getPosition().y == getPosition().y) {
                return false;
            }
        }
        return population > 1;
    }

} // namespace turn_strategy