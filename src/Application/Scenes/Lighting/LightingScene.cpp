// forward declare
#include "App.h"
// class
#include "LightingScene.h"

namespace lighting_scene {
    LightingScene::LightingScene(App& theApp)
    : Scene(theApp),
      mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()),
      mGui_(*this) {
        assembleResources();

        mBackgroundColor_ = {0.0f, 0.0f, 0.0f, 1.f};
        getFocusCamera()->setPosition({0,.1,5});

        {
            // Light source
            mpLight_ = new LightEntity(*this);
            mpLight_->setPosition({0,1,0});
            mpLight_->setColor({10,10,10,1});
            mEntities_.push_back(std::unique_ptr<LightEntity>(mpLight_));
        }
        {
            // Cube 1
            std::unique_ptr<Entity> assimpEntity = std::make_unique<Entity>(*this);
            ModelRenderable* assimpRenderable = assimpEntity->addRenderable<ModelRenderable>();
            assimpRenderable->setModel(mResources_.getResource<Model>("Cube"));
            assimpRenderable->setShader(getApp().getResources().getResource<Shader>("AssimpLight"));

            assimpEntity->setPosition({1.f, 0.f, 0.f});
            mEntities_.push_back(std::move(assimpEntity));
        }
        {
            // Cube 2
            std::unique_ptr<Entity> assimpEntity = std::make_unique<Entity>(*this);
            ModelRenderable* assimpRenderable = assimpEntity->addRenderable<ModelRenderable>();
            assimpRenderable->setModel(mResources_.getResource<Model>("Cube"));
            assimpRenderable->setShader(getApp().getResources().getResource<Shader>("AssimpLight"));

            assimpEntity->setPosition({-1.f, 0.f, 0.f});
            mEntities_.push_back(std::move(assimpEntity));
        }
    }

    LightingScene::~LightingScene() {}

    /**
     * Update the Scene
     * @param dt Time since last update in seconds
     */
    void LightingScene::update(const float dt) {
        mApp_.getRenderer().enableGammaCorrect(true);
        mCameraController_.update(dt);
    }

    /**
     * Render this scene
     * @param renderer Rendering helper
     */
    void LightingScene::render(Renderer& renderer) {
        renderer.setBloom(true);
        renderer.setCamera(getFocusCamera());
        renderer.setLightSources({mpLight_->getLightSource()});
        for (int i = 0; i < mEntities_.size(); ++i) {
            mEntities_[i]->render(renderer);
        }
        renderer.setBloom(false);
    }

    void LightingScene::renderGUI() {
        mGui_.render();
    }

    void LightingScene::assembleResources() {
        // Cube
        std::unique_ptr<Model> cubeModel = std::make_unique<Model>();
        cubeModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("Cube")
        );
        mResources_.addResource(std::move(cubeModel), "Cube");
        // Plane
        std::unique_ptr<Model> planeModel = std::make_unique<Model>();
        planeModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("RectPlane")
        );
        mResources_.addResource(std::move(planeModel), "RectPlane");
        // Sphere
        std::unique_ptr<Model> sphereModel = std::make_unique<Model>();
        sphereModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("Sphere")
        );
        mResources_.addResource(std::move(sphereModel), "Sphere");
    }

    std::vector<std::unique_ptr<Entity>>& LightingScene::getEntities() {
        return mEntities_;
    }

} // namespace lighting_scene
