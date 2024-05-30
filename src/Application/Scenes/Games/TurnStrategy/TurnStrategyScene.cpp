#include "TurnStrategyScene.h"
#include "App.h"

namespace turn_strategy {

    TurnStrategyScene::TurnStrategyScene(App& theApp)
        : Scene(theApp), mGui_(*this), game(*this, *getFocusCamera()) {
        mBackgroundColor_ = {.5,.5,1,1.f};
    }

    TurnStrategyScene::~TurnStrategyScene() {
        delete mpFocusCamera_;
    }

    void TurnStrategyScene::update(const float dt) {
        game.update(dt);
    }

    void TurnStrategyScene::render(Renderer& renderer) {
        game.render(renderer, *getFocusCamera());
        mGui_.render();
    }

    void TurnStrategyScene::onKeyPress(unsigned int code) {}

    void TurnStrategyScene::onKeyRelease(unsigned int code) {}

    void TurnStrategyScene::onMousePress(const InputHandler::MouseEvent& mouseEvent) {
        game.onMousePress(mouseEvent);
    }

    void TurnStrategyScene::onMouseRelease(const InputHandler::MouseEvent& mouseEvent) {
        game.onMouseRelease(mouseEvent);
    }

    void TurnStrategyScene::onMouseWheel(const InputHandler::MouseEvent& mouseEvent) {
        game.onMouseWheel(mouseEvent);
    }

    TurnStrategyGame& TurnStrategyScene::getGame() {
        return game;
    }

} // namespace turn_strategy