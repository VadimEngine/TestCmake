#include "BasicScene.h"
#include "App.h"

BasicScene::BasicScene(App& theApp)
    : Scene(theApp), mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()), mGui_(*this) {
    // Shader* theShader = new Shader("src/Shaders/MVPTexShader.vert", "src/Shaders/MVPTexShader.frag");
    Shader* theShader = new Shader("src/Shaders/Assimp.vert", "src/Shaders/Assimp.frag");

    mBackgroundColor_ = {.4,.4,.4,1.f};
    getFocusCamera()->setPosition({0,0,5});
    // TODO use this texture
    unsigned int texId = Texture::loadTexture("res/V.png");
    
    Model* cubeModel = new Model();
    cubeModel->addMesh(Mesh::getLoadedMesh("Cube").value());
    
    Entity* theEntity = new Entity();

    Model* theModel = new Model();
    theModel->loadMesh("res/Cube.obj");
    ModelRenderable* model1 = new ModelRenderable(theModel, theShader);\

    model1->setWireframeRendering(true);
    theEntity->addRenderable(model1);

    SpriteSheet* mpSpriteSheet_ = new SpriteSheet( Texture::loadTexture("res/Sprites.png"), {512, 512}, {16,16});
    SpriteSheet::Sprite* mSprite1_ = new SpriteSheet::Sprite(mpSpriteSheet_, glm::ivec2(0, 0));

    SpriteRenderable* sprite1 = new SpriteRenderable(mSprite1_);

    theEntity->addRenderable(sprite1);

    mEntities_.push_back(theEntity);
}

BasicScene::~BasicScene() {
    delete mpFocusCamera_;
    // TODO delete Entities
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
