#pragma once
#include "ImGuiComponent.h"
#include <vector>

class Scene2d;

class Scene2dGUI : public ImGuiComponent {
private:
    Scene2d* mpScene_ = nullptr;
    bool mVsyncEnabled_ = false;

public:
    Scene2dGUI(Scene2d* theScene);

    ~Scene2dGUI();

    void buildImGui() override;

};