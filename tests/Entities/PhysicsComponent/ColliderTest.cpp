// Third party
#include <gtest/gtest.h>
// Project
#include "App.h"
#include "Scene.h"
#include "Entity.h"

/**
 * @brief Simple scene for tests only
 */
class TestScene : public Scene {
public:
    TestScene(App& theApp) 
    : Scene(theApp), sampleEntity(*this) {
        assembleResources();
        mBackgroundColor_ = {1,0,0,1};
        // With this orthogonal camera, screen size is 4 wide and 3 height
        mpFocusCamera_->setMode(Camera::CameraMode::ORTHOGONAL);
        mpFocusCamera_->setPosition({0,0,1});
        // this model will be a white 1x1 (relative to camera projection) rectangle
        ModelRenderable* rectRenderable = sampleEntity.addRenderable<ModelRenderable>();
        rectRenderable->setModel(mResources_.getResource<Model>("RectPlane"));
        rectRenderable->setShader(getApp().getResources().getResource<Shader>("Assimp"));

        sampleEntity.addPhysicsComponent<BoxCollider2D>();
    }

    /**
     * Update the Scene
     * @param dt Time since last update in seconds
     */
    void update(const float dt) override {}

    /**
     * Render this scene
     * @param renderer Rendering helper
     */
    void render(Renderer& renderer) override {
        renderer.setCamera(getFocusCamera());
        sampleEntity.render(renderer);
    }

    /**
     * @brief Loads and builds resources that are used for this scene
     */
    void assembleResources() override {
        std::unique_ptr<Model> planeModel = std::make_unique<Model>();
        planeModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("RectPlane")
        );
        mResources_.addResource(std::move(planeModel), "RectPlane");
    }
    /**  Simple Entity */
    Entity sampleEntity;
};

/**
 * @brief Test that collider behaves as expected
 */
TEST(ColliderTest, Initialization) {
    /*
     make a scene with 2 entities with colliders (mixture of square and circle
     - test that colliders work when not colliding, enter colliding and exit collide
     - test mouse-ray collision works 

    */
    Camera theCamera;
    glm::vec3 cameraPosition = theCamera.getPosition();
    EXPECT_TRUE(cameraPosition.x == 0);
    EXPECT_TRUE(cameraPosition.y == 0);
    EXPECT_TRUE(cameraPosition.z == 0);
}