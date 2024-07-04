#include "App.h"
#include "Scene2d.h"

namespace scene_2d {
    Scene2d::Scene2d(App& theApp)
        : Scene(theApp),
        mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()),
        mGui_(*this),
        mSprite1_(*mApp_.getResources().getResource<SpriteSheet>("SpriteSheet1"), glm::ivec2(0, 0)),
        mSprite2_(*mApp_.getResources().getResource<SpriteSheet>("SpriteSheet1"), glm::ivec2(1, 0)) {
        mpFocusCamera_->setPosition({0,0,5});

        std::unique_ptr<Entity> theEntity1 = std::make_unique<Entity>(*this);
        SpriteRenderable* sprite1Renderable1 = new SpriteRenderable(&mSprite1_);
        theEntity1->addRenderable(sprite1Renderable1);
        mEntities_.push_back(std::move(theEntity1));

        std::unique_ptr<Entity> theEntity2 = std::make_unique<Entity>(*this);
        SpriteRenderable* sprite1Renderable2 = new SpriteRenderable(&mSprite2_);
        theEntity2->addRenderable(sprite1Renderable2);
        theEntity2->setPosition({1.f, 0.f, 0.f});
        mEntities_.push_back(std::move(theEntity2));
    }

    Scene2d::~Scene2d() {}

    void Scene2d::update(const float dt) {
        mCameraController_.update(dt);
    }

    void Scene2d::render(Renderer& renderer) {
        for (int i = 0; i < mEntities_.size(); i++) {
            mEntities_[i]->render(renderer, *getFocusCamera());
        }
        mGui_.render();
    }

    void Scene2d::assembleResources() {
    }

    std::vector<std::unique_ptr<Entity>>& Scene2d::getEntities() {
        return mEntities_;
    }

} // namespace scene_2d