#include "MenuScene.h"
#include "App.h"

namespace menu_scene {
    MenuScene::MenuScene(App& theApp)
        : Scene(theApp), mGui_(*this) {}

    MenuScene::~MenuScene() {}

    void MenuScene::update(const float dt) {}

    void MenuScene::render(Renderer& renderer) {
        mGui_.render();
    }
} // namespace menu_scene