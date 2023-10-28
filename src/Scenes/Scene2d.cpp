#include "App.h"
#include "Scene2d.h"

Scene2d::Scene2d(App& theApp)
    :Scene(theApp), mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()), mGui_(*this), 
     mSpriteSheet_(Texture::getLoadedTexture("SpriteSheet").value(), {512, 512}, {16,16}),
     mSprite1_(&mSpriteSheet_, glm::ivec2(0, 0)), mSprite2_(&mSpriteSheet_, glm::ivec2(1, 0))  {

    mpFocusCamera_->setPosition({0,0,5});

    Entity* theEntity1 = new Entity();
    SpriteRenderable* sprite1Renderable1 = new SpriteRenderable(&mSprite1_);
    theEntity1->addRenderable(sprite1Renderable1);
    mEntities_.push_back(theEntity1);

    Entity* theEntity2 = new Entity();
    SpriteRenderable* sprite1Renderable2 = new SpriteRenderable(&mSprite2_);
    theEntity2->addRenderable(sprite1Renderable2);
    theEntity2->setPosition({1.f, 0.f, 0.f});
    mEntities_.push_back(theEntity2);
}

Scene2d::~Scene2d() {
    delete mpFocusCamera_;
}

void Scene2d::update(const float dt) {
    mCameraController_.update(dt);
}

void Scene2d::render(Renderer& renderer) {
    for (int i = 0; i < mEntities_.size(); i++) {
        mEntities_[i]->render(renderer, *getFocusCamera());
    }
    mGui_.render();
}

std::vector<Entity*>& Scene2d::getEntities() {
    return mEntities_;
}