#include "BasicScene.h"
#include "App.h"

BasicScene::BasicScene(App& theApp)
    : Scene(theApp),
    mCameraController_(getFocusCamera(), 
    mApp_.getWindow().getInputHandler()), 
    mGui_(*this),
    mSpriteSheet_(
        mApp_.getResources().getResource<Texture>("SpriteSheet")->getId(), 
        {512, 512}, 
        {16,16}
    ),
    mSprite_(&mSpriteSheet_, glm::ivec2(0, 0)) {
    // load/build resources
    assembleResources();

    mBackgroundColor_ = {.4,.4,.4,1.f};
    getFocusCamera()->setPosition({0,.1,5});

    // First Entity
    std::unique_ptr<Entity> theEntity1 = std::make_unique<Entity>(*this);
    // Solid cube properties
    ModelRenderable* solidCubeRenderable = new ModelRenderable(
        mResources_.getResource<Model>("Cube"), 
        getApp().getResources().getResource<Shader>("Assimp")
    );
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
    theEntity1->setPosition({0.f, .5f, 0.f});
    mEntities_.push_back(std::move(theEntity1));

    // Second Entity
    std::unique_ptr<Entity> theEntity2 = std::make_unique<Entity>(*this);
    ModelRenderable* textureCubeRenderable = new ModelRenderable(
        mResources_.getResource<Model>("Cube"), 
        getApp().getResources().getResource<Shader>("MVPTexShader")
    );
    // Texture cube properties
    textureCubeRenderable->setTexture(
        0, 
        mApp_.getResources().getResource<Texture>("SampleTexture")->getId(),
        "uTexture"
    );

    theEntity2->addRenderable(textureCubeRenderable);
    // Second Entity properties
    theEntity2->setPosition({3.f, .5f, 0.f});
    mEntities_.push_back(std::move(theEntity2));

    // Third Entity (Floor)
    std::unique_ptr<Entity> floorEntity = std::make_unique<Entity>(*this);
    ModelRenderable* floorRenderable = new ModelRenderable(
        mResources_.getResource<Model>("RectPlane"), 
        getApp().getResources().getResource<Shader>("Assimp")
    );

    // Plane Renderable properties
    floorRenderable->setRotation({-90, 0, 0});
    floorRenderable->setScale({10, 10, 0});
    floorRenderable->setColor({0.f, 0.f, 0.f, 1.0f});
    // Add renderable to floor entity
    floorEntity->addRenderable(floorRenderable);
    mEntities_.push_back(std::move(floorEntity));

    std::unique_ptr<Entity> assimpEntity = std::make_unique<Entity>(*this);
    ModelRenderable* assimpRenderable = new ModelRenderable(
        mResources_.getResource<Model>("Sphere"), 
        getApp().getResources().getResource<Shader>("Assimp")
    );
    assimpEntity->addRenderable(assimpRenderable);
    assimpEntity->setPosition({0.f, 5.f, 0.f});
    mEntities_.push_back(std::move(assimpEntity));

    std::unique_ptr<Entity> planeTexture = std::make_unique<Entity>(*this);
    ModelRenderable* planeTextureRenderable = new ModelRenderable(
        mResources_.getResource<Model>("RectPlane"), 
        getApp().getResources().getResource<Shader>("TextureSurface")
    );
    // Texture. TODO allow imgui set this from list of textures
    planeTextureRenderable->setTexture(
        0, 
        mApp_.getResources().getResource<Texture>("SpriteSheet")->getId(),
        "uTexture"
    );
    planeTextureRenderable->setSubTextureTopLeft({0.f, 0.f});
    planeTextureRenderable->setSubTextureSize({16.f/512.f, 16.f/512.f});

    planeTexture->addRenderable(planeTextureRenderable);
    planeTexture->setPosition({-2.f, 2.f, 0.f});
    mEntities_.push_back(std::move(planeTexture));
}

BasicScene::~BasicScene() {
    delete mpFocusCamera_;
}

void BasicScene::update(float dt) {
    mCameraController_.update(dt);
}

void BasicScene::render(Renderer& renderer) {
    for (int i = 0; i < mEntities_.size(); i++) {
        mEntities_[i]->render(renderer, *getFocusCamera());
    }
    
    glm::mat4 translationMatrix2 = glm::translate(glm::mat4(1.0f), {0.f, 0.f, 0.f});
    renderer.renderTextNormalized(
        "TEST STRING", 
        translationMatrix2, 
        *getFocusCamera(), 
        *(mApp_.getResources().getResource<Font>("Consolas")), 
        .01f, 
        {1,0,0}
    );
    

    mGui_.render();
}

void BasicScene::assembleResources() {
    // Cube
    std::unique_ptr<Model> cubeModel = std::make_unique<Model>();
    cubeModel->addSharedMesh(
        mApp_.getResources().getResource<Mesh>("Cube")
    );
    mResources_.addResource(std::move(cubeModel), "Cube");
    // Plane
    std::unique_ptr<Model> planeModel = std::make_unique<Model>();;
    planeModel->addSharedMesh(
        mApp_.getResources().getResource<Mesh>("RectPlane")
    );
    mResources_.addResource(std::move(planeModel), "RectPlane");
    // Sphere
    std::unique_ptr<Model> sphereModel = std::make_unique<Model>();;
    sphereModel->addSharedMesh(
        mApp_.getResources().getResource<Mesh>("Sphere")
    );
    mResources_.addResource(std::move(sphereModel), "Sphere");
}

std::vector<std::unique_ptr<Entity>>& BasicScene::getEntities() {
    return mEntities_;
}
