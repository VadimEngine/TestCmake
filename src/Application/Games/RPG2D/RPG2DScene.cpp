#include "RPG2DScene.h"
#include "App.h"

namespace RPG2D {

    RPG2DScene::RPG2DScene(App& theApp)
        : Scene(theApp), mGui_(*this), mGame_(mApp_, *getFocusCamera()) {
        getFocusCamera()->setPosition({0,0,10});
    }

    RPG2DScene::~RPG2DScene() {
        delete mpFocusCamera_;
    }

    void RPG2DScene::update(const float dt) {
        mGame_.update(dt);
    }

    void RPG2DScene::render(Renderer& renderer) {
        mGame_.render(renderer, *getFocusCamera());
        mGui_.render();
    }

    void RPG2DScene::onKeyPress(unsigned int code) {
        mGame_.onKeyPress(code);
    }

    void RPG2DScene::onKeyRelease(unsigned int code) {
    }

    void RPG2DScene::onMousePress(const InputHandler::MouseEvent& mouseEvent) {
        mGame_.onMousePress(mouseEvent);
    }



} // namespace RPG2D