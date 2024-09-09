// forward declare
#include "App.h"
// class
#include "GamesScene.h"

GamesScene::GamesScene(App& theApp)
    : Scene(theApp), mGui_(*this) {}

GamesScene::~GamesScene() {}

void GamesScene::update(float dt) {}

void GamesScene::render(Renderer& renderer) {
    renderer.setCamera(getFocusCamera());
}

void GamesScene::renderGUI() {
    mGui_.render();
}
