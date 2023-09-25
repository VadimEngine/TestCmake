#include "ShadedObject.h"

ShadedObject::ShadedObject(Shader* theShader)
: mpShader_(theShader) {
    glGenVertexArrays(1, &mVAO_);
    glGenBuffers(1, &mVBO_);

    glBindVertexArray(mVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO_);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

ShadedObject::~ShadedObject() {}

template <typename T>
void ShadedObject::setAttributes(const std::vector<AttribDetail>& attribs) {
    glBindVertexArray(mVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO_);
    // calculate stride
    unsigned int strideSize = 0;
    unsigned int attribElementsCount = 0;

    for (unsigned int i = 0; i < attribs.size(); i++) {
        strideSize += attribs[i].elements * sizeof(T);
        attribElementsCount += attribs[i].elements;
    }

    mElementsPerVertex_ = attribElementsCount;

    int lastPointer = 0;

    // assign attributes
    for (unsigned int i = 0; i < attribs.size(); i++) {
        glVertexAttribPointer(
            i,
            attribs[i].elements,
            attribs[i].type,
            attribs[i].normalized,
            strideSize,
            (void*)lastPointer
        );
        glEnableVertexAttribArray(i);
        lastPointer += attribs[i].elements * sizeof(T);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ShadedObject::setVertices(const std::vector<float>& vertices, const std::vector<float> indices) {
    glBindVertexArray(mVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO_);
    // Dynamic vs static vs stream?
    if (vertices.empty()) {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    } else {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
    }

    mVertices_ = vertices;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

    glBindVertexArray(mVAO_);
    glDrawArrays(GL_TRIANGLES, 0,  mVertices_.size() / mElementsPerVertex_);

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
    glBindVertexArray(mVAO_);

    mpShader_->bind();
    glUniform1i(glGetUniformLocation(mpShader_->getProgramId(), "texture0"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId);
    mTexId_ = texId;
}

// instantiate template for expected types
template void ShadedObject::setAttributes<float>(const std::vector<AttribDetail>& attribs);

