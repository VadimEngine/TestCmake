#include "TurnStrategyScene.h"
#include "App.h"

namespace turn_strategy {

    TurnStrategyScene::TurnStrategyScene(App& theApp)
    : Scene(theApp), mGui_(*this) {
        assembleResources();
        mBackgroundColor_ = {.5,.5,1,1.f};
        mpGame_ = std::make_unique<TurnStrategyGame>(*this);
    }

    TurnStrategyScene::~TurnStrategyScene() {}

    void TurnStrategyScene::assembleResources() {
        mResources_.loadResource<Texture>(
            {Resource::RESOURCE_PATH / "World1.png"},
            "World1"
        );
        // Rectangle Plane Model
        std::unique_ptr<Model> rectModel = std::make_unique<Model>();
        rectModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("RectPlane")
        );
        mResources_.addResource(std::move(rectModel), "RectPlane");
    }

    void TurnStrategyScene::update(const float dt) {
        mpGame_->update(dt);
    }

    void TurnStrategyScene::render(Renderer& renderer) {
        mpGame_->render(renderer, *getFocusCamera());
        mGui_.render();
    }

    void TurnStrategyScene::onKeyPress(unsigned int code) {}

    void TurnStrategyScene::onKeyRelease(unsigned int code) {}

    void TurnStrategyScene::onMousePress(const InputHandler::MouseEvent& mouseEvent) {
        mpGame_->onMousePress(mouseEvent);
    }

    void TurnStrategyScene::onMouseRelease(const InputHandler::MouseEvent& mouseEvent) {
        mpGame_->onMouseRelease(mouseEvent);
    }

    void TurnStrategyScene::onMouseWheel(const InputHandler::MouseEvent& mouseEvent) {
        mpGame_->onMouseWheel(mouseEvent);
    }

    TurnStrategyGame& TurnStrategyScene::getGame() {
        return *mpGame_.get();
    }

} // namespace turn_strategy