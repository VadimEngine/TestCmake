#include "BasicScene.h"
#include "App.h"

BasicScene::BasicScene(App& theApp)
    : Scene(theApp), mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()), mGui_(*this), 
    mSpriteSheet_(Texture::getLoadedTexture("SpriteSheet").value(), {512, 512}, {16,16}), mSprite_(&mSpriteSheet_, glm::ivec2(0, 0)),
    mSolidCubeRenderable_(&mCubeModel_, Shader::getLoadedShader("Assimp")), mSpriteRenderable_(&mSprite_), mTextureCubeRenderable_(&mCubeModel_, Shader::getLoadedShader("MVPTexShader")),
    mFloorRenderable_(&mPlaneModel_, Shader::getLoadedShader("Assimp")) {

    mBackgroundColor_ = {.4,.4,.4,1.f};
    getFocusCamera()->setPosition({0,.1,5});

    mCubeModel_.addMesh(*(Mesh::getLoadedMesh("Cube")));
    mPlaneModel_.addMesh(*(Mesh::getLoadedMesh("Plane")));
    
    // First Entity
    Entity* theEntity1 = new Entity();
    // Solid cube properties
    mSolidCubeRenderable_.setWireframeRendering(true);
    mSolidCubeRenderable_.setColor({.3f, .3f, .3f, 1.0f});
    // Add Cube to Entity
    theEntity1->addRenderable(&mSolidCubeRenderable_);
    // Set sprite properties
    mSpriteRenderable_.setColor({.3f, 0.f, 0.f, 1.0f});
    mSpriteRenderable_.setPosition({0.f, 1.f, 0.f});
    // Add sprite to Entity 
    theEntity1->addRenderable(&mSpriteRenderable_);
    // First entity properties
    theEntity1->setPosition({0.f, 1.f, 0.f});
    mEntities_.push_back(theEntity1);

    // Second Entity
    Entity* theEntity2 = new Entity();
    theEntity2->addRenderable(&mTextureCubeRenderable_);
    // Texture cube properties
    mTextureCubeRenderable_.setTexture(0, Texture::getLoadedTexture("SampleTexture").value());
    // Second Entity properties
    theEntity2->setPosition({3.f, 1.f, 0.f});
    mEntities_.push_back(theEntity2);

    // Third Entity (Floor)
    Entity* floorEntity = new Entity();
    // Plane Renderable properties
    mFloorRenderable_.setRotation({-90, 0, 0});
    mFloorRenderable_.setScale({10, 10, 0});
    mFloorRenderable_.setColor({0.f, 0.f, 0.f, 1.0f});
    // Add renderable to floor entity
    floorEntity->addRenderable(&mFloorRenderable_);
    mEntities_.push_back(floorEntity);
}

BasicScene::~BasicScene() {
    delete mpFocusCamera_;
    // Delete Entities
    for (auto eachEntity: mEntities_) {
        delete eachEntity;
    }
}

void BasicScene::update(float dt) {
    mCameraController_.update(dt);
}

void BasicScene::render(Renderer& renderer) {
    for (int i = 0; i < mEntities_.size(); i++) {
        mEntities_[i]->render(renderer, *getFocusCamera());
    }
    mGui_.render();
}

std::vector<Entity*>& BasicScene::getEntities() {
    return mEntities_;
}
