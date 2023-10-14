#include "ModelRenderable.h"

ModelRenderable::ModelRenderable(Model* pModel, Shader* pShader)
    : mpModel_(pModel), mpShader_(pShader) {}

ModelRenderable::~ModelRenderable() {}

void ModelRenderable::render(const Renderer& theRenderer, const Camera& theCamera, const glm::mat4& parentModelMat) const {
    glm::mat4 model = glm::mat4(1.0f);
    
    // translation matrix for position
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), mPosition_);
    //rotation matrix
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), glm::radians(mRotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
    // scale matrix
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), mScale_);

    glm::mat4 localModelMat  = translationMatrix * rotationMatrix * scaleMatrix;
    
    mpShader_->bind();
    mpShader_->setMat4("model", parentModelMat * localModelMat);
    mpShader_->setMat4("view", theCamera.getViewMatrix());
    mpShader_->setMat4("projection",  theCamera.getProjectionMatrix());
    mpModel_->render(*mpShader_);

    if (drawWireframe_) {
        // Enable wire frame
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        mpShader_->setBool("wireframeMode",true);
        // Render wire frame
        mpModel_->render(*mpShader_);

        // revert back to non-wireframe
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        mpShader_->setBool("wireframeMode", false);
    }
}

void ModelRenderable::setModel(Model* pModel) {
    mpModel_ = pModel;
}

void ModelRenderable::setShader(Shader* pShader) {
    mpShader_ = pShader;
}

void ModelRenderable::setWireframeRendering(const bool enable) {
    drawWireframe_ = enable;
}

Model* ModelRenderable::getModel() const {
    return mpModel_;
}

Shader* ModelRenderable::getShader() const {
    return mpShader_;
}