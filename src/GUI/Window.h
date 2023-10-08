#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "InputHandler.h"

class Window {
private:
    static constexpr unsigned int SCR_WIDTH = 800;
    static constexpr unsigned int SCR_HEIGHT = 600;

    GLFWwindow* mpGLFWWindow_ = nullptr;

    InputHandler mInputHandler_;
    unsigned int mSwapInterval_ = 1;

public:
    Window();

    ~Window();

    void update(float dt);

    void render();

    GLFWwindow* getGLFWWindow() const;

    bool isRunning() const;

    void setVSync(const bool enabled);

    int getGLFWSwapInterval();


    InputHandler* getInputHandler();

};