#include "BasicScene.h"
#include "App.h"
#include "BasicScene.h"
#include <iostream>

// TODO look into Batch Sprite Rendering

BasicScene::BasicScene(App* theApp)
    : Scene(theApp), cameraController(getFocusCamera(), mpApp_->getWindow()->getInputHandler()), mGui_(this) {

    mpShader_ = new Shader("src/Shaders/MVPTexShader.vert", "src/Shaders/MVPTexShader.frag");

    texId = Texture::loadTexture("res/V.png");
    
    Model* cubeModel = new Model();
    cubeModel->addMesh(Mesh::loadedMeshByName.find("Cube2")->second);
    
    mShadedObject = new ShadedObject(mpShader_); 
    mShadedObject->setModel(cubeModel);
    mShadedObject->setTexture(texId);
    // TODO free texture?
}

void BasicScene::update(float dt) {
    cameraController.update(dt);
    mShadedObject->update(dt);
}

void BasicScene::render(Renderer& renderer) {
    mpShader_->bind();

    // Draw normal
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    mShadedObject->getShader()->setBool("wireframeMode", false);
    mShadedObject->render(*getFocusCamera());

    // draw wireframe
    mShadedObject->getShader()->setBool("wireframeMode",true);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    mShadedObject->render(*getFocusCamera());

    mGui_.render();
}
