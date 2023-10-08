#include "Scene.h"
#include "App.h"

Scene::Scene(App* theApp, glm::vec3 cameraPosition)
    : mpApp_(theApp) {
        mFocusCamera_ = new Camera(cameraPosition);
}

void Scene::setBackgroundColor(glm::vec4 newColor) {
    mBackgroundColor_ = newColor;
}

glm::vec4 Scene::getBackgroundColor() const {
    return mBackgroundColor_;
}

App* Scene::getApp() {
    return mpApp_;
}

Camera* Scene::getFocusCamera() {
    return mFocusCamera_;
}
