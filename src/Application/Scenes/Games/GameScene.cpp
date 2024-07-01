#include "GamesScene.h"
#include "App.h"

GamesScene::GamesScene(App& theApp)
    : Scene(theApp), mGui_(*this) {}

GamesScene::~GamesScene() {
    delete mpFocusCamera_;
}

void GamesScene::update(float dt) {}

void GamesScene::render(Renderer& renderer) {
    mGui_.render();
}
