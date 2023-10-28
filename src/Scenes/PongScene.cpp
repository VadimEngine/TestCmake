#include "PongScene.h"
#include "App.h"

PongScene::PongScene(App& theApp)
    : Scene(theApp), mGui_(*this) {}

PongScene::~PongScene() {}

void PongScene::update(const float dt) {
    for (int i = 0; i < mEntities_.size(); i++) {
        mEntities_[i]->update(dt);
    }
}

void PongScene::render(Renderer& renderer) {
    for (int i = 0; i < mEntities_.size(); i++) {
        mEntities_[i]->render(renderer, *getFocusCamera());
    }
    mGui_.render();
}

std::vector<Entity*>& PongScene::getEntities() {
    return mEntities_;
}