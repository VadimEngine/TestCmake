#include "ShadedObject.h"

ShadedObject::ShadedObject(Shader* theShader)
: mpShader_(theShader) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices_.size() * sizeof(float), mVertices_.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
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

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glDrawArraysInstanced
    glBindVertexArray(0);
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
    glBindVertexArray(VAO);

    mpShader_->bind();
    glUniform1i(glGetUniformLocation(mpShader_->getProgramId(), "texture0"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId);
    mTexId_ = texId;
}
