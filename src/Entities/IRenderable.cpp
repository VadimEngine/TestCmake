#include "IRenderable.h"

void IRenderable::setEnabled(const bool isEnabled) {
    mEnabled_ = isEnabled;
}

bool IRenderable::isEnabled() const {
    return mEnabled_;
}

glm::vec3 IRenderable::getPosition() const {
    return mPosition_;
}

glm::vec3 IRenderable::getRotation() const {
    return mRotation_;
}

glm::vec3 IRenderable::getScale() const {
    return mScale_;
}

void IRenderable::setPosition(const glm::vec3& newPosition) {
    mPosition_ = newPosition;
}

void IRenderable::setRotation(const glm::vec3& newRotation) {
    mRotation_ = newRotation;
}

void IRenderable::setScale(const glm::vec3& newScale) {
    mScale_ = newScale;
}