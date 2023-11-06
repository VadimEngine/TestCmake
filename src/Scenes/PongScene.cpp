#include "PongScene.h"
#include "App.h"

PongScene::PongScene(App& theApp)
    : Scene(theApp), mGui_(*this), mGame_(mApp_) {
    getFocusCamera()->setPosition({0,0,10});
}

PongScene::~PongScene() {
    delete mpFocusCamera_;
}

void PongScene::update(const float dt) {
    mGame_.update(dt);
}

void PongScene::render(Renderer& renderer) {
    mGame_.render(renderer, *getFocusCamera());
    mGui_.render();
}

void PongScene::onKeyPress(unsigned int code) {
    mGame_.onKeyPress(code);
}

void PongScene::onKeyRelease(unsigned int code) {}