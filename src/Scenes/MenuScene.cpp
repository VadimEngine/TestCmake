#include "MenuScene.h"
#include "App.h"

MenuScene::MenuScene(App* theApp)
    : Scene(theApp) {
    mpMenuPage_ = new MenuGUI(this);
}

void MenuScene::update(const float dt) {}

void MenuScene::render(Renderer& renderer) {
    mpMenuPage_->render();
}
