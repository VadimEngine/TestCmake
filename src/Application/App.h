#pragma once
#define GLEW_STATIC
#include <chrono>
#include <GL/glew.h>
#include <iostream>
#include "MenuPage.h"
#include "Window.h"
#include "BasicScene.h"

class App {
private:
    std::chrono::steady_clock::time_point mLastTime_;
    MenuPage* mpMenuPage_;
    BasicScene* mpScene_;
    Window mWindow_;
public:
    App();
    ~App();
    
    void run();

    void update();
    void render();

    bool isRunning();

    private:
    /**
     * Initialize OpenGL
     */
    static void initializeOpenGL();
    
};