#include "Scene.h"
#include "App.h"

Scene::Scene(App* theApp, glm::vec3 cameraPosition)
    : mpApp_(theApp) {
        mFocusCamera_ = new Camera(cameraPosition);
    }

App* Scene::getApp() {
    return mpApp_;
}

Camera* Scene::getFocusCamera() {
    return mFocusCamera_;
}
