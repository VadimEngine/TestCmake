#pragma once
#define GLEW_STATIC
#include <chrono>
#include <GL/glew.h>
#include "Window.h"
#include "BasicScene.h"
#include "MenuScene.h"
#include "AssimpScene.h"
#include "Logger.h"

class App {
private:
    std::chrono::steady_clock::time_point mLastTime_;
    Scene* mpScene_;
    Window mWindow_;
public:
    App();
    ~App();
    
    void run();

    void update();

    void render();

    bool isRunning();
    
    void quit();

    void setScene(Scene* newScene);

    Window* getWindow();

private:
    /**
     * Initialize OpenGL
     */
    static void initializeOpenGL();
};