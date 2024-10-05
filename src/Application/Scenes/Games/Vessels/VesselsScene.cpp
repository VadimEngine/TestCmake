// forward declare
#include "App.h"
// class
#include "VesselsScene.h"

namespace vessels {
   VesselsScene::VesselsScene(App& theApp)
    : Scene(theApp), 
     mGui_(*this) {
        assembleResources();
        mpGame_ = std::make_unique<VesselsGame>(*this);
     }

    VesselsScene::~VesselsScene() {}

    void VesselsScene::update(float dt) {
        mpGame_->update(dt);
    }

    void VesselsScene::render(Renderer& renderer)  {
        renderer.setCamera(getFocusCamera());
        mpGame_->render(renderer);
    }

    void VesselsScene::renderGUI() {
        mGui_.render();
    }

    void VesselsScene::onMousePress(const InputHandler::MouseEvent& mouseEvent) {}

    void VesselsScene::assembleResources() {
        std::unique_ptr<Model> rectModel = std::make_unique<Model>();
        rectModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("RectPlane")
        );
        mResources_.addResource(std::move(rectModel), "RectPlane");
        // Cube
        std::unique_ptr<Model> cubeModel = std::make_unique<Model>();
        cubeModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("Cube")
        );
        mResources_.addResource(std::move(cubeModel), "Cube");
    }

    VesselsGame& VesselsScene::getGame() {
        return *mpGame_.get();
    }

} // namespace vessels
