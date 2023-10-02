#pragma once
#include "ImGuiComponent.h"

class MenuScene;

class MenuGUI: public ImGuiComponent {
private:
    MenuScene* mpScene_;
public:
    MenuGUI(MenuScene* theScene);

    ~MenuGUI();

    void buildImGui() override;
};