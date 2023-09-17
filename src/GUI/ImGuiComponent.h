#pragma once
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <stdexcept>

class ImGuiComponent {
protected:
    bool mIsRemove_ = false;

public:
    ImGuiComponent();

    virtual ~ImGuiComponent() = 0;

    static void initializeImGui(GLFWwindow* window);

    static void deinitialize();

    static void startRender();
    virtual void buildImGui();
    static void endRender();

    void render();

    void setRemove(const bool remove);

    bool isRemove() const;
};