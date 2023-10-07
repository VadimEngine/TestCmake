#pragma once
#include "ImGuiComponent.h"
#include <vector>

class Scene2d;

class Scene2dGUI : public ImGuiComponent {
private:
    Scene2d* mpScene_ = nullptr;

    // TODO move this to 1 place or make static since this is always the same
    std::vector<float> mVertices_ = {
        // position     // uv
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };

public:
    Scene2dGUI(Scene2d* theScene);

    ~Scene2dGUI();

    void buildImGui() override;

};