#include "Entity.h"

Entity::Entity() {}

Entity::~Entity() {}

void Entity::update(float dt) {}

void Entity::render(Renderer& theRenderer, Camera& theCamera) {
    glm::mat4 model = glm::mat4(1.0f);
    
    // translation matrix for position
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), mPosition_);
    //rotation matrix
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), glm::radians(mRotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
    // scale matrix
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), mScale_);

    for (const IRenderable* eachRenderable : mRenderableComponents_) {
        if (eachRenderable->isEnabled()) {
            eachRenderable->render(theRenderer, theCamera, translationMatrix * rotationMatrix * scaleMatrix);
        }
    }
}

std::vector<IRenderable*>& Entity::getRenderableComponents() {
    return mRenderableComponents_;
}

void Entity::addRenderable(IRenderable* newRenderable) {
    mRenderableComponents_.push_back(newRenderable);
}

glm::vec3 Entity::getPosition() const {
    return mPosition_;
}

glm::vec3 Entity::getRotation() const {
    return mRotation_;
}

glm::vec3 Entity::getScale() const {
    return mScale_;
}

void Entity::setPosition(const glm::vec3& newPosition) {
    mPosition_ = newPosition;
}

void Entity::setRotation(const glm::vec3& newRotation) {
    mRotation_ = newRotation;
}

void Entity::setScale(const glm::vec3& newScale) {
    mScale_ = newScale;
}