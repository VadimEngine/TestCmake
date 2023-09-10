#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

class Window {
    static constexpr unsigned int SCR_WIDTH = 800;
    static constexpr unsigned int SCR_HEIGHT = 600;

    GLFWwindow* mpGLFWWindow_ = nullptr;
public:
    Window();

    ~Window();

    void update(float dt);

    void render();

    GLFWwindow* getGLFWWindow() const;

    bool isRunning() const;

};