#include "BasicScene.h"
#include "App.h"

#include <iostream>

// TODO look into Batch Sprite Rendering

BasicScene::BasicScene(App* theApp)
    : Scene(theApp), mCamera_({0,0,0}), cameraController(&mCamera_, mpApp_->getWindow()->getInputHandler()) {

    // mpShader_ = new Shader("src/Shaders/MVPShader.vert", "src/Shaders/MVPShader.frag");
    mpShader_ = new Shader("src/Shaders/MVPTexShader.vert", "src/Shaders/MVPTexShader.frag");

    texId = Texture::loadTexture("res/V.png");
    mShadedObject = new ShadedObject(mpShader_); 
    mShadedObject->setPosition({0,0,-5});
    mShadedObject->setTexture(texId);
    mShadedObject->setAttributes<float>({
        {3, GL_FLOAT, GL_FALSE}, // Position
        {2, GL_FLOAT, GL_FALSE}, // UV
    });
    mShadedObject->setVertices(Model::loadedModelsByName["XYZuvCube"], {});

    //mShadedObject2 = new ShadedObject(mpShader_);
    //mShadedObject2->setPosition({0,1,-5});
    //mShadedObject2->setTexture(texId);
    // TODO free texture?
}

void BasicScene::update(float dt) {
    cameraController.update(dt);
    mShadedObject->update(dt);
    //mShadedObject2->update(dt);
}

void BasicScene::render() {
    mShadedObject->render(mCamera_);
    //mShadedObject2->render(mCamera_);
}
