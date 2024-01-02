#include "App.h"

bool App::sOpenGLInitialized_ = false;

App::App() 
 : mWindow_("OpenGL Application", 800, 600) {
    // Initialize OpenGL, imgui and load resources
    initializeOpenGL();
    ImGuiComponent::initializeImGui(mWindow_.getGLFWWindow());
    Texture::loadTextures();
    Shader::loadShaders();
    Mesh::loadMeshes();
    // Create Scene and renderer (must be called after OpenGL is initialized)
    mpRenderer_ = new Renderer(800, 600);
    mScenes_.push_back(new MenuScene(*this));
}

App::~App() {
    // Clean Application resources
    ImGuiComponent::deinitialize();
    glfwTerminate();
    delete mpRenderer_;
    Mesh::releaseMeshes();
    // Play "0" audio to clear audio buffer
    mAudioManger_.playSound(0);
    AudioManager::freeLoadedAudios();
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
    // Update list in reverse order and delete any marked for removal
    for (auto it = mScenes_.rbegin(); it != mScenes_.rend();) {
        if ((*it)->isRemove()) {
            it = std::list<Scene*>::reverse_iterator(mScenes_.erase(std::next(it).base()));
        } else {
            (*it)->update(dt.count());
            it++;
        }
    }
    InputHandler& handler = getWindow().getInputHandler();

    // Propagate key events to the scenes
    while (const auto keyEvent = handler.getKeyEvent()) {
        for (auto it = mScenes_.rbegin(); it != mScenes_.rend(); it++) {
            if (keyEvent.value().getType() == InputHandler::KeyEvent::Type::PRESS) {
                (*it)->onKeyPress(keyEvent.value().getCode());
            } else if (keyEvent.value().getType() == InputHandler::KeyEvent::Type::RELEASE) {
                (*it)->onKeyRelease(keyEvent.value().getCode());
            }
        }
    }

    // Propagate mouse events to scenes
    while (const auto mouseEvent = handler.getMouseEvent()) {
        for (auto it = mScenes_.rbegin(); it != mScenes_.rend(); it++) {
            if (mouseEvent.value().getType() == InputHandler::MouseEvent::Type::PRESS) {
                (*it)->onMousePress(mouseEvent.value());
            } else if (mouseEvent.value().getType() == InputHandler::MouseEvent::Type::RELEASE) {
                (*it)->onMouseRelease(mouseEvent.value());
            } else if (mouseEvent.value().getType() == InputHandler::MouseEvent::Type::SCROLL_UP ||
                mouseEvent.value().getType() == InputHandler::MouseEvent::Type::SCROLL_DOWN) {
                (*it)->onMouseWheel(mouseEvent.value());
            }
        }
    }
}

void App::render() {
    // Set background color from scene
    if (!mScenes_.empty()) {
        glm::vec4 sceneBackgroundColor = mScenes_.front()->getBackgroundColor();
        glClearColor(sceneBackgroundColor.r, sceneBackgroundColor.g, sceneBackgroundColor.b, sceneBackgroundColor.a);
    } else {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Render list in reverse order
    for (auto it = mScenes_.rbegin(); it != mScenes_.rend(); it++) {
       (*it)->render(*mpRenderer_);
    }
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
    mScenes_.push_back(newScene);
}

Window& App::getWindow() {
    return mWindow_;
}

void App::setAntiAliasing(unsigned int sampleSize) {
    // Set sample size
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
        glEnable(GL_DEPTH_TEST); // Enable z-buffer
        // Needed for text rendering
        glEnable(GL_BLEND);
        // Set Depth test to replace the current fragment if the z is less then OR equal
        glDepthFunc(GL_LEQUAL); 
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable alpha drawing

        sOpenGLInitialized_ = true;
    }
}

AudioManager& App::getAudioManger() {
    return mAudioManger_;
}