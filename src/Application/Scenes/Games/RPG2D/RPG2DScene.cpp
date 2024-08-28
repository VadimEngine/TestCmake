// forward declare
#include "App.h"
// class
#include "RPG2DScene.h"

namespace rpg_2d {

    RPG2DScene::RPG2DScene(App& theApp)
        : Scene(theApp), mGui_(*this), mGame_(*this, *getFocusCamera()) {
        getFocusCamera()->setPosition({0,0,10});
        mApp_.getRenderer().enableGammaCorrect(false);
    }

    RPG2DScene::~RPG2DScene() {}

    void RPG2DScene::update(const float dt) {
        mGame_.update(dt);
    }

    void RPG2DScene::render(Renderer& renderer) {
        renderer.setCamera(getFocusCamera());
        mGame_.render(renderer);
    }

    void RPG2DScene::renderGUI() {
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

} // namespace rpg_2d