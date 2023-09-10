#pragma once
#include "ImGuiComponent.h"

class MenuPage: public ImGuiComponent {
public:
    MenuPage();

    ~MenuPage();

    void buildImGui() override;

};