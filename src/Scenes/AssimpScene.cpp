#include "AssimpScene.h"
#include "App.h"
#include <iostream>

AssimpScene::AssimpScene(App* theApp) 
     : Scene(theApp), cameraController(getFocusCamera(), mpApp_->getWindow()->getInputHandler()), mGui_(this) {

    mpShader_ =  new Shader("src/Shaders/Assimp.vert", "src/Shaders/Assimp.frag");
    myModel = new Model();
    myModel->loadMesh("res/Cube.obj");
}

void AssimpScene::update(const float dt) {
    cameraController.update(dt);
}

void AssimpScene::render(Renderer& renderer) {
    mpShader_->bind();
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    //model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    glm::mat4 projection = getFocusCamera()->getProjectionMatrix();
    glm::mat4 view = getFocusCamera()->getViewMatrix();

    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), modelPosition);
    //rotation matrix
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), glm::radians(modelRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(modelRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(modelRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    // scale matrix
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), modelScale);

    mpShader_->setMat4("model", translationMatrix * rotationMatrix * scaleMatrix);
    mpShader_->setMat4("view", view);
    mpShader_->setMat4("projection", projection);
    
    // draw normal
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    mpShader_->setBool("wireframeMode", false);
    myModel->render(*mpShader_);

    // draw wireframe
    mpShader_->setBool("wireframeMode",true);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    myModel->render(*mpShader_);

    
    mGui_.render();
}