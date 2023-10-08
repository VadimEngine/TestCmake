#include "App.h"
#include "AssimpScene.h"
#include "AssimpGUI.h"

AssimpGUI::AssimpGUI(AssimpScene* theScene)
    :mpScene_(theScene) {}

AssimpGUI::~AssimpGUI() {}

void AssimpGUI::buildImGui() {
    Camera* pCamera = mpScene_->getFocusCamera();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings");
    ImGui::Text("Assimp Scene");
    ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));
    ImGui::Text("Camera");
    ImGui::Text(
        "Position: %.2f, %.2f, %.2f",
        pCamera->getPosition().x,
        pCamera->getPosition().y,
        pCamera->getPosition().z
    );
    ImGui::Text(
        "Rotation: %.2f, %.2f, %.2f",
        pCamera->getRotation().x,
        pCamera->getRotation().y,
        pCamera->getRotation().z
    );
    ImGui::Text("FOV: %.2f", pCamera->getFOV());
    ImGui::Separator();

    float position[3] = {
        mpScene_->modelPosition.x,
        mpScene_->modelPosition.y,
        mpScene_->modelPosition.z
    };
    float rotation[3] = {
        mpScene_->modelRotation.x,
        mpScene_->modelRotation.y,
        mpScene_->modelRotation.z
    };
    float scale[3] = {
        mpScene_->modelScale.x,
        mpScene_->modelScale.y,
        mpScene_->modelScale.z
    };
    ImGui::Text("Model:");
    if (ImGui::SliderFloat3("Position##Model", position, -10.f, 10.f, "%.2f")) {
        mpScene_->modelPosition.x = position[0];
        mpScene_->modelPosition.y = position[1];
        mpScene_->modelPosition.z = position[2];
    }

    if (ImGui::SliderFloat3("Rotation##Model", rotation, -10.f, 10.f, "%.2f")) {
        mpScene_->modelRotation.x = rotation[0];
        mpScene_->modelRotation.y = rotation[1];
        mpScene_->modelRotation.z = rotation[2];
    }

    if (ImGui::SliderFloat3("Scale##Model", scale, -10.f, 10.f, "%.2f")) {
        mpScene_->modelScale.x = scale[0];
        mpScene_->modelScale.y = scale[1];
        mpScene_->modelScale.z = scale[2];
    }
    if (ImGui::Button("Back")) {
        mpScene_->getApp()->setScene(new MenuScene(mpScene_->getApp()));
    }
    ImGui::End();
};