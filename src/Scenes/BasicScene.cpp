#include "BasicScene.h"
#include "App.h"

#include <iostream>

// TODO look into Batch Sprite Rendering

BasicScene::BasicScene(App* theApp)
    : Scene(theApp), mCamera_({0,0,0}), cameraController(&mCamera_, mpApp_->getWindow()->getInputHandler()) {

    // mpShader_ = new Shader("src/Shaders/MVPShader.vert", "src/Shaders/MVPShader.frag");
    mpShader_ = new Shader("src/Shaders/MVPTexShader.vert", "src/Shaders/MVPTexShader.frag");

    texId = Texture::loadTexture("src/res/V.png");
    mShadedObject = new ShadedObject(mpShader_); 
    mShadedObject->setPosition({0,0,0});
    mShadedObject->setTexture(texId);

    mShadedObject2 = new ShadedObject(mpShader_);
    mShadedObject2->setPosition({0,1,0});
    mShadedObject2->setTexture(texId);
    mShadedObject2->setRotationOrigin({0,.5,0});
    // TODO free texture?
}

void BasicScene::update(float dt) {
    cameraController.update(dt);
    mShadedObject->update(dt);
    mShadedObject2->update(dt);
}

void BasicScene::render() {
    mShadedObject->render(mCamera_);
    mShadedObject2->render(mCamera_);
}
