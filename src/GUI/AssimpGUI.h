#pragma once
#include "ImGuiComponent.h"

class AssimpScene;

class AssimpGUI: public ImGuiComponent {
private:
    AssimpScene* mpScene_ = nullptr;
public:
    AssimpGUI(AssimpScene* theScene);

    ~AssimpGUI();

    void buildImGui() override;
};