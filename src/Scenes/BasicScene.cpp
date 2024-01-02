#include "BasicScene.h"
#include "App.h"

BasicScene::BasicScene(App& theApp)
    : Scene(theApp), mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()), mGui_(*this),
    mSpriteSheet_(Texture::getLoadedTexture("SpriteSheet").value(), {512, 512}, {16,16}), mSprite_(&mSpriteSheet_, glm::ivec2(0, 0)) {

    mBackgroundColor_ = {.4,.4,.4,1.f};
    getFocusCamera()->setPosition({0,.1,5});

    mCubeModel_.addMesh(*(Mesh::getLoadedMesh("Cube")));
    mPlaneModel_.addMesh(*(Mesh::getLoadedMesh("RectPlane")));
    
    // First Entity
    Entity* theEntity1 = new Entity();
    // Solid cube properties
    ModelRenderable* solidCubeRenderable = new ModelRenderable(&mCubeModel_, Shader::getLoadedShader("Assimp"));
    solidCubeRenderable->setWireframeRendering(true);
    solidCubeRenderable->setColor({.3f, .3f, .3f, 1.0f});
    // Add Cube to Entity
    theEntity1->addRenderable(solidCubeRenderable);
    // Set sprite properties
    SpriteRenderable* spriteRenderable = new SpriteRenderable(&mSprite_);
    spriteRenderable->setColor({.3f, 0.f, 0.f, 1.0f});
    spriteRenderable->setPosition({0.f, 1.f, 0.f});
    // Add sprite to Entity 
    theEntity1->addRenderable(spriteRenderable);
    // First entity properties
    theEntity1->setPosition({0.f, 1.f, 0.f});
    mEntities_.push_back(theEntity1);

    // Second Entity
    Entity* theEntity2 = new Entity();
    ModelRenderable* textureCubeRenderable = new ModelRenderable(&mCubeModel_, Shader::getLoadedShader("MVPTexShader"));
    // Texture cube properties
    textureCubeRenderable->setTexture(0, Texture::getLoadedTexture("SampleTexture").value());
    theEntity2->addRenderable(textureCubeRenderable);
    // Second Entity properties
    theEntity2->setPosition({3.f, 1.f, 0.f});
    mEntities_.push_back(theEntity2);

    // Third Entity (Floor)
    Entity* floorEntity = new Entity();
    ModelRenderable* floorRenderable = new ModelRenderable(&mPlaneModel_, Shader::getLoadedShader("Assimp"));

    // Plane Renderable properties
    floorRenderable->setRotation({-90, 0, 0});
    floorRenderable->setScale({10, 10, 0});
    floorRenderable->setColor({0.f, 0.f, 0.f, 1.0f});
    // Add renderable to floor entity
    floorEntity->addRenderable(floorRenderable);
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

    glm::mat4 translationMatrix2 = glm::translate(glm::mat4(1.0f), {0.f, 0.f, 0.f});
    renderer.renderTextNormalized("TEST STRING", translationMatrix2, *getFocusCamera(), .01f, {1,0,0});

    mGui_.render();
}

std::vector<Entity*>& BasicScene::getEntities() {
    return mEntities_;
}
