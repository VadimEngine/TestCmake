#pragma once
#include "ImGuiComponent.h"

class BasicScene;

class BasicSceneGUI: public ImGuiComponent {
private:
    BasicScene* mpScene_ = nullptr;
public:
    BasicSceneGUI(BasicScene* theScene);

    ~BasicSceneGUI();

    void buildImGui() override;
};