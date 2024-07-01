#include "MenuScene.h"
#include "App.h"

MenuScene::MenuScene(App& theApp)
    : Scene(theApp), mGui_(*this) {}

MenuScene::~MenuScene() {
    delete mpFocusCamera_;
}

void MenuScene::update(const float dt) {}

void MenuScene::render(Renderer& renderer) {
    mGui_.render();
}
