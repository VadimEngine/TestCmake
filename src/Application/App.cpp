#include "App.h"

App::App() {
    initializeOpenGL();
    Model::loadModels();
    ImGuiComponent::initializeImGui(mWindow_.getGLFWWindow());
    mpScene_ = new BasicScene(this);
    mpMenuPage_ = new MenuPage();
}

App::~App() {
    // Clean up
    ImGuiComponent::deinitialize();
    glfwTerminate();
}

void App::run() {
    while (isRunning()) {
        update();
        render();
    }
}

void App::update() {
    // Calculate time since last update
    std::chrono::duration<float, std::deci> dt = (std::chrono::high_resolution_clock::now() - mLastTime_);
    mLastTime_ = std::chrono::high_resolution_clock::now();
    // Update application content
    mWindow_.update(dt.count());
    mpScene_->update(dt.count());
}

void App::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mpScene_->render();
    mpMenuPage_->render();
    // Render GUI
    mWindow_.render();
}

bool App::isRunning() {
    return mWindow_.isRunning();
}

/**
 * Initialize OpenGL
 */
void App::initializeOpenGL() {
   glewExperimental = true;

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        LOG_E("Glew Init failed");
        throw std::runtime_error("GLEW Init error");
    }
    // glEnable(GL_CULL_FACE);// Default is counter clockwise
    // Enable alpha drawing
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST); // Enable z-buffer

    // Anti aliasing
    //glfwWindowHint(GLFW_SAMPLES, 4);
    //glEnable(GL_MULTISAMPLE);
}

Window* App::getWindow() {
    return &mWindow_;
}
