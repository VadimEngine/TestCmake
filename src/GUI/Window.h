#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "InputHandler.h"
#include <string>
#include <glm/vec2.hpp>

class Window {
private:
    /** Default Screen Width */
    static constexpr unsigned int SCR_WIDTH = 800;
    /** Default Screen Height */
    static constexpr unsigned int SCR_HEIGHT = 600;
    /** GLFW window this window wraps */
    GLFWwindow* mpGLFWWindow_ = nullptr;
    /** Input handler listening to inputs on this window*/
    InputHandler mInputHandler_;
    /** GLFW swap interval for VSync */
    unsigned int mSwapInterval_ = 1;

public:
    /** Constructor */
    Window(const std::string& windowLbl = "", int width = SCR_WIDTH, int height = SCR_HEIGHT);

    /** Destructor */
    ~Window();

    /** 
     * Update the window (mainly polls for inputs)
     * \param dt Time since last update in seconds
     */
    void update(float dt);

    /** Render the window content */
    void render();

    /** Get the GLFW window */
    GLFWwindow* getGLFWWindow() const;

    /** If the Window is currently running */
    bool isRunning() const;

    /** 
     * Enable/Disable VSync
     * \param enabled VSync status
     */
    void setVSync(const bool enabled);

    /** Get the GLFW swap interaval */
    int getGLFWSwapInterval();

    /** Get the screen dimension of this window*/
    glm::vec2 getWindowDimensions();

    /** Get the input handler listening to this Window's inputs */
    InputHandler& getInputHandler();
};