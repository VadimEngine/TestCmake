#include "App.h"

bool App::sOpenGLInitialized_ = false;

App::App() {
    // Initialize OpenGL, imgui and load resources
    initializeOpenGL();
    ImGuiComponent::initializeImGui(mWindow_.getGLFWWindow());
    Mesh::loadMeshes();
    // Create Scene and renderer (must be called after OpenGL is initialized)
    mpRenderer_ = new Renderer();
    mpScene_ = new MenuScene(this);
}

App::~App() {
    // Clean Application resources
    ImGuiComponent::deinitialize();
    glfwTerminate();
    delete mpRenderer_;
    delete mpScene_;
}

void App::run() {
    // Update and render while application is running
    while (isRunning()) {
        update();
        render();
    }
}

void App::update() {
    // Calculate time since last update (in seconds)
    std::chrono::duration<float> dt = (std::chrono::high_resolution_clock::now() - mLastTime_);
    mLastTime_ = std::chrono::high_resolution_clock::now();
    // Update application content
    mWindow_.update(dt.count());
    mpScene_->update(dt.count());
}

void App::render() {
    // Set background color from scene
    glm::vec4 sceneBackgroundColor = mpScene_->getBackgroundColor();
    glClearColor(sceneBackgroundColor.r, sceneBackgroundColor.g, sceneBackgroundColor.b, sceneBackgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //mpScene_->render();
    mpScene_->render(*mpRenderer_);
    mWindow_.render();
}

bool App::isRunning() const {
    // TODO more running conditions. For now running is when the window is open
    return mWindow_.isRunning();
}

void App::quit() {
    // TODO do any saving
    // Set window to close
    glfwSetWindowShouldClose(mWindow_.getGLFWWindow(), true);
}

void App::setScene(Scene* newScene) {
    // Delete old Scene and set the new Scene
    if (mpScene_ != nullptr) {
        delete mpScene_;
    }
    mpScene_ = newScene;
}

Window& App::getWindow() {
    return mWindow_;
}

void App::setAntiAliasing(unsigned int sampleSize) {
    // Set samplesize
    glfwWindowHint(GLFW_SAMPLES, sampleSize);
    // Enable/disable anti-aliasing based on sample size
    if (sampleSize != 0) {
        glEnable(GL_MULTISAMPLE);
    } else {
        glDisable(GL_MULTISAMPLE);
    }
}

void App::initializeOpenGL() {
    // Only initialize if this if the first time
    if (!sOpenGLInitialized_) {
        glewExperimental = true;

        GLenum err = glewInit();
        if (GLEW_OK != err) {
            LOG_E("Glew Init failed");
            throw std::runtime_error("GLEW Init error");
        }
        glEnable(GL_CULL_FACE);// Default is counter clockwise
        // Enable alpha drawing
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST); // Enable z-buffer


        sOpenGLInitialized_ = true;
    }
}
