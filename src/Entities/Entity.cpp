#include "Entity.h"

Entity::Entity() {}

Entity::~Entity() {
    // Delete Renderables
    for (auto& it: mRenderableComponents_) {
        delete it;
    }
    // Delete Physics Components
    for (auto& it: mPhysicsComponents_) {
        delete it.second;
    }
}

void Entity::update(float dt) {
    for (auto& it: mPhysicsComponents_) {
        it.second->update(dt);
    }
    mPosition_ += mVelocity_ * dt;
}

void Entity::render(const Renderer& theRenderer, const Camera& theCamera) const{
    glm::mat4 model = glm::mat4(1.0f);
    
    // translation matrix for position
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), mPosition_);
    // rotation matrix
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), glm::radians(mRotation_.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.z), glm::vec3(0.0f, 0.0f, 1.0f));
    // scale matrix
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), mScale_);

    const glm::mat4 modelMat = translationMatrix * rotationMatrix * scaleMatrix;
    for (const BaseRenderable* eachRenderable : mRenderableComponents_) {
        if (eachRenderable->isEnabled()) {
            eachRenderable->render(theRenderer, theCamera, modelMat);
        }
    }
}

void Entity::renderHighlight(const Renderer& theRenderer, const Camera& theCamera) const {
    // TODO how to set a color for this?
    getCollider()->render(theRenderer, theCamera);
}

std::vector<BaseRenderable*>& Entity::getRenderableComponents() {
    return mRenderableComponents_;
}

void Entity::addRenderable(BaseRenderable* newRenderable) {
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

glm::vec3 Entity::getVelocity() const {
    return mVelocity_;
}

void Entity::setPosition(const glm::vec3& newPosition) {
    mPosition_ = newPosition;
    if (mCollider_ != nullptr) {
        mCollider_->setPosition(newPosition);
    }
}

void Entity::setRotation(const glm::vec3& newRotation) {
    mRotation_ = newRotation;
}

void Entity::setScale(const glm::vec3& newScale) {
    mScale_ = newScale;
}

void Entity::setVelocity(const glm::vec3& newVelocity) {
    mVelocity_ = newVelocity;
}

void Entity::setCollider2(Collider2* newCollider) {
    mCollider_ = newCollider;
}

Collider2* Entity::getCollider() const {
    return mCollider_;
}

template<typename T>
void Entity::addPhysicsComponent() {
    T* component = new T(*this);
    mPhysicsComponents_[component->getType()] = component;
}

template<typename T>
T* Entity::getPhysicsComponent() {
    // Use a temporary Component to get the seeking type
    auto it = mPhysicsComponents_.find(T(*this).getType());
    if (it != mPhysicsComponents_.end()) {
        return dynamic_cast<T*>(it->second);
    }
    return nullptr;
}

// Explicit instantiate template for expected types
template void Entity::addPhysicsComponent<RigidBodyComponent>();
template RigidBodyComponent* Entity::getPhysicsComponent<RigidBodyComponent>();
