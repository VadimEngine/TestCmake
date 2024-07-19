#include "PongScene.h"
#include "App.h"

namespace pong {
    PongScene::PongScene(App& theApp)
    : Scene(theApp), mGui_(*this) {
        assembleResources();
        mpGame_ = std::make_unique<PongGame>(*this);
    }

    PongScene::~PongScene() {}

    void PongScene::update(const float dt) {
        mpGame_->update(dt);
    }

    void PongScene::render(Renderer& renderer) {
        mpGame_->render(renderer, *getFocusCamera());
        mGui_.render();
    }

    void PongScene::assembleResources() {
        // Circle Plane Model
        std::unique_ptr<Model> circleModel = std::make_unique<Model>();
        circleModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("CircularPlane")
        );
        mResources_.addResource(std::move(circleModel), "CircularPlane");
        // Rectangle Plane Model
        std::unique_ptr<Model> rectModel = std::make_unique<Model>();
        rectModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("RectPlane")
        );
        mResources_.addResource(std::move(rectModel), "RectPlane");
    }

    void PongScene::onKeyPress(unsigned int code) {
        if (!ImGuiComponent::keyboardGUIFocus()) {
            mpGame_->onKeyPress(code);
        }
    }

    void PongScene::onKeyRelease(unsigned int code) {}

    PongGame& PongScene::getGame() {
        return *(mpGame_.get());
    }

} // namespace pong