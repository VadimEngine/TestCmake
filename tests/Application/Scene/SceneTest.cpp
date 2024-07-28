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
        std::unique_ptr<Model> planeModel = std::make_unique<Model>();;
        planeModel->addSharedMesh(
            mApp_.getResources().getResource<Mesh>("RectPlane")
        );
        mResources_.addResource(std::move(planeModel), "RectPlane");
    }
    /**  Simple Entity */
    Entity sampleEntity;
};

/**
 * @brief Test fixture class for Scene tests
 */
class SceneTest : public ::testing::Test {
protected:
    void SetUp() override {
        app = new App();
        scene = new TestScene(*app);
        app->setScene(scene);
        // Render the scene
        app->render();
    }

    void TearDown() override {
        // App owns scene so it will delete the scene
        delete app; 
    }

    App* app;
    TestScene* scene;
};

/**
 * @brief Test that confirms that scene with a simple Renderable will render it as expected
 */
TEST_F(SceneTest, SimpleRender) {
    // get drawn buffer
    int width, height;
    glfwGetFramebufferSize(app->getWindow().getGLFWWindow(), &width, &height);
    // Confirm buffer size
    EXPECT_EQ(width, app->getWindow().getWindowDimensions().x);
    EXPECT_EQ(height, app->getWindow().getWindowDimensions().y);

    std::vector<unsigned char> pixels(4 * width * height); // Assuming RGBA format
    // after 1 render call, the content is in the front buffer
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    glm::vec4 backgroundColor = scene->getBackgroundColor();
    uint32_t backgroundColorInt = (static_cast<uint32_t>(backgroundColor.r * 255) << 24) |
                                  (static_cast<uint32_t>(backgroundColor.g * 255) << 16) |
                                  (static_cast<uint32_t>(backgroundColor.b * 255) << 8) |
                                  static_cast<uint32_t>(backgroundColor.a * 255);
    glm::vec2 center = {width / 2, height / 2};
    glm::vec2 oneXoneSize = {width / 4, height / 3};

    // expect pixel to be background color except in center 1x1 region
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int id = (i * width + j) * 4;
            // Combine RGBA channels into one int
            uint32_t pixelValue = (static_cast<unsigned int>(pixels[id]) << 24) |    // Red
                                  (static_cast<unsigned int>(pixels[id + 1]) << 16) | // Green
                                  (static_cast<unsigned int>(pixels[id + 2]) << 8)  | // Blue
                                  static_cast<unsigned int>(pixels[id + 3]);        // Alpha
                                  
            if (i >= center.y - (oneXoneSize.y / 2) && i < center.y + (oneXoneSize.y / 2)
                && j >= center.x - (oneXoneSize.x / 2) && j < center.x + (oneXoneSize.x / 2)) {
                // Model rendered here
                EXPECT_EQ(pixelValue, 0xFFFFFFFF) << "Failed at: " << i << ", " << j;
            } else {
                // background
                EXPECT_EQ(pixelValue, backgroundColorInt) << "Failed at: " << i << ", " << j;
            }
        }
    }
}