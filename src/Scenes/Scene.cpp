#include "Scene.h"
#include "App.h"

Scene::Scene(App& theApp)
    : mApp_(theApp), mpFocusCamera_(new Camera()) {
    // Set camera ascpet ratio
    glm::vec2 screenDim = mApp_.getWindow().getWindowDimensions();
    mpFocusCamera_->setAspectRatio(static_cast<float>(screenDim.x)/static_cast<float>(screenDim.y));
}

void Scene::setBackgroundColor(glm::vec4 newColor) {
    mBackgroundColor_ = newColor;
}

glm::vec4 Scene::getBackgroundColor() const {
    return mBackgroundColor_;
}

App& Scene::getApp() {
    return mApp_;
}

Camera* Scene::getFocusCamera() {
    return mpFocusCamera_;
}

bool Scene::isRemove() const {
    return mIsRemove_;
}

void Scene::setRemove(const bool remove) {
    mIsRemove_ = remove;
}

void Scene::onKeyPress(unsigned int code) {}

void Scene::onKeyRelease(unsigned int code) {}

void Scene::onMousePress(const InputHandler::MouseEvent& mouseEvent) {}

void Scene::onMouseRelease(const InputHandler::MouseEvent& mouseEvent) {}

void Scene::onMouseWheel(const InputHandler::MouseEvent& mouseEvent) {}