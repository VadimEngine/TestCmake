#include "Scene.h"
#include "App.h"

Scene::Scene(App& theApp)
    : mApp_(theApp), mpFocusCamera_(new Camera()) {}

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
