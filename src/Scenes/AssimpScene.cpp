#include "AssimpScene.h"
#include "App.h"

AssimpScene::AssimpScene(App& theApp) 
     : Scene(theApp), mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()), mGui_(*this) {
    getFocusCamera()->setPosition({0,0,5});

    mpShader_ = new Shader("src/Shaders/Assimp.vert", "src/Shaders/Assimp.frag");

    mModel_.loadMesh("res/Cube.obj");
    mBackgroundColor_ = {.4,.4,.4,1.f};

    Entity* theEntity = new Entity();
    ModelRenderable* modelRenderable = new ModelRenderable(&mModel_, mpShader_);
    modelRenderable->setWireframeRendering(true); 
    theEntity->addRenderable(modelRenderable);
    mEntities_.push_back(theEntity);
}

AssimpScene::~AssimpScene() {
    delete mpFocusCamera_;
    delete mpShader_;
    // TODO delete Entities
}

void AssimpScene::update(const float dt) {
    mCameraController_.update(dt);
}

void AssimpScene::render(Renderer& renderer) {
    for (int i = 0; i < mEntities_.size(); i++) {
        mEntities_[i]->render(renderer, *getFocusCamera());
    }

    // Render GUI
    mGui_.render();
}

std::vector<Entity*>& AssimpScene::getEntities() {
    return mEntities_;
}