#include "ShadedObject.h"

ShadedObject::ShadedObject(Shader* theShader)
: mpShader_(theShader) {}

ShadedObject::~ShadedObject() {}

void ShadedObject::setModel(Model* theModel) {
    mModel_ = theModel;
}

void ShadedObject::update(float dt) {}

void ShadedObject::render(const Camera& theCamera) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = theCamera.getProjectionMatrix();
    glm::mat4 view = theCamera.getViewMatrix();

    glBindTexture(GL_TEXTURE_2D, mTexId_);
    mpShader_->bind();

    // translation matrix for position
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), mPosition_);
    glm::mat4 originTranslationMatrix = glm::translate(glm::mat4(1.0f), mRotationOrigin_);
    glm::mat4 inverseOriginTranslationMatrix = glm::translate(glm::mat4(1.0f), -mRotationOrigin_);
    //rotation matrix
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), glm::radians(mRotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
    // scale matrix
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), mScale_);

    mpShader_->setMat4("model", translationMatrix * originTranslationMatrix * rotationMatrix * inverseOriginTranslationMatrix * scaleMatrix);
    mpShader_->setMat4("view", view);
    mpShader_->setMat4("projection", projection);
    // mpShader_->setVec4("uColor", { 1.0f, 0.0f, 0.0f, 1.0f });

    mModel_->render(*mpShader_);
}

void ShadedObject::setPosition(glm::vec3 newPosition) {
    mPosition_ = newPosition;
}

void ShadedObject::setRotation(glm::vec3 newRotation) {
    mRotation_ = newRotation;
}

void ShadedObject::setRotationOrigin(glm::vec3 newOrigin) {
    mRotationOrigin_ = newOrigin;
}

void ShadedObject::setScale(glm::vec3 newScale) {
    mScale_ = newScale;
}

void ShadedObject::setTexture(unsigned int texId) {
    mpShader_->bind();
    glUniform1i(glGetUniformLocation(mpShader_->getProgramId(), "texture0"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId);
    mTexId_ = texId;
}

Shader* ShadedObject::getShader() {
    return mpShader_;
}
