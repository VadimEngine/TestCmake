#include "App.h"

App::App() {
    initializeOpenGL();
    Mesh::loadMeshes();
    ImGuiComponent::initializeImGui(mWindow_.getGLFWWindow());
    mpScene_ = new MenuScene(this);
    mRenderer_ = new Renderer();
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
    glClearColor(.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //mpScene_->render();
    mpScene_->render(*mRenderer_);
    mWindow_.render();
}

bool App::isRunning() {
    return mWindow_.isRunning();
}

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

    // TODO allow enable/disable vsync
}

void App::quit() {
    // Set window to close
    glfwSetWindowShouldClose(mWindow_.getGLFWWindow(), true);
}

void App::setScene(Scene* newScene) {
    if (mpScene_ != nullptr) {
        delete mpScene_;
    }
    mpScene_ = newScene;
}

Window* App::getWindow() {
    return &mWindow_;
}
