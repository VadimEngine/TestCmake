#include "Window.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    //get width and height
    int winHeight;
    int winWidth;

    glfwGetWindowSize(window, &winWidth, &winHeight);

    GLfloat mx = ((2.0f * xpos / winWidth) - 1.0f);
    GLfloat my = (1.0f - (2.0f * ypos / winHeight));
    //((Window*)glfwGetWindowUserPointer(window))->getHandler()->mouseCoords = glm::vec2(mx, my);
    //((Window*)glfwGetWindowUserPointer(window))->getHandler()->setMousePosition(glm::vec2(mx, my));
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window* windowWrapper = static_cast<Window*>(glfwGetWindowUserPointer(window));
    InputHandler& inputHandler = windowWrapper->getInputHandler();
    
    if (action == GLFW_PRESS) {
        inputHandler.onKeyPressed(key);
    }
    if (action == GLFW_RELEASE) {
        inputHandler.onKeyReleased(key);
    }
    // GLFW_REPEAT
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

Window::Window() {
    if (!glfwInit()) {
        throw std::runtime_error("glfwInit failed");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Context profiles are only defined for OpenGL version 3.2 and above
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    mpGLFWWindow_ = glfwCreateWindow(640, 480, "Simple GLFW Window", NULL, NULL);
    if (mpGLFWWindow_ == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwSetWindowUserPointer(mpGLFWWindow_, this);
    glfwMakeContextCurrent(mpGLFWWindow_);
    glfwSwapInterval(1);
    glfwSetKeyCallback(mpGLFWWindow_, keyCallback);
    // glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetFramebufferSizeCallback(mpGLFWWindow_, framebuffer_size_callback);
    // glfwSetWindowFocusCallback(mpGLFWWindow_, windowFocusCallback);
    /*
    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetCursorEnterCallback(window, mouse_enter_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    */
}

Window::~Window() {
    glfwDestroyWindow(mpGLFWWindow_);
    glfwTerminate();
}

void Window::update(float dt) {
    glfwPollEvents();
}

void Window::render() {
    // Draw on the window
    glfwSwapBuffers(mpGLFWWindow_);
}

GLFWwindow* Window::getGLFWWindow() const {
    return mpGLFWWindow_;
}

bool Window::isRunning() const {
    return !glfwWindowShouldClose(mpGLFWWindow_);
}

void Window::setVSync(const bool enabled) {
    mSwapInterval_ = static_cast<int>(enabled);
    glfwSwapInterval(mSwapInterval_);
}

int Window::getGLFWSwapInterval() {
    return mSwapInterval_;
}

InputHandler& Window::getInputHandler() {
    return mInputHandler_;
}
