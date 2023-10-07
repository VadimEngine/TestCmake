#include "App.h"
#include "Scene2d.h"
#include "Scene2dGUI.h"

Scene2dGUI::Scene2dGUI(Scene2d* theScene) 
    : mpScene_(theScene) {

}

Scene2dGUI::~Scene2dGUI() {

}

void Scene2dGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings");
    ImGui::Text("Scene 2D");
    ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));
    ImGui::Separator();

    // TODO sprite position and rotation
    // TODO camera properies (perspective and orthogonal)

    static int cameraMode = static_cast<int>(mpScene_->getFocusCamera()->getMode());

    ImGui::Text("Camera");
    ImGui::Text("Camera Mode");
    if (ImGui::RadioButton("Perspective", &cameraMode, 0)) {
        mpScene_->getFocusCamera()->setMode(static_cast<Camera::CameraMode>(cameraMode));
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Orthogonal", &cameraMode, 1)) {
        mpScene_->getFocusCamera()->setMode(static_cast<Camera::CameraMode>(cameraMode));
    }

    ImGui::Text("Camera Movement");
    glm::vec3 camPosition = mpScene_->getFocusCamera()->getPosition();
    ImGui::Text(
        "Position: %.2f %.2f %.2f",
        camPosition.x,
        camPosition.y,
        camPosition.z
    );
    glm::vec3 camForward = mpScene_->getFocusCamera()->getForward();
    ImGui::Text(
        "Direction: %.2f %.2f %.2f",
        camForward.x,
        camForward.y,
        camForward.z
    );
    ImGui::Text(
        "FOV: %.2f",
        mpScene_->getFocusCamera()->getFOV()
    );

    ImGui::Separator();
    /*
    float position[3] = {
        mpScene_->mSprite2d_.mPosition_.x,
        mpScene_->mSprite2d_.mPosition_.y,
        mpScene_->mSprite2d_.mPosition_.z
    };
    float rotation[3] = {
        mpScene_->mSprite2d_.mRotation_.x,
        mpScene_->mSprite2d_.mRotation_.y,
        mpScene_->mSprite2d_.mRotation_.z
    };
    float scale[3] = {
        mpScene_->mSprite2d_.mScale_.x,
        mpScene_->mSprite2d_.mScale_.y,
        mpScene_->mSprite2d_.mScale_.z
    };
    */
    ImGui::Text("Model:");
    /*
    if (ImGui::SliderFloat3("Position##Model", position, -10.f, 10.f, "%.2f", 0.1f)) {
        mpScene_->mSprite2d_.mPosition_.x = position[0];
        mpScene_->mSprite2d_.mPosition_.y = position[1];
        mpScene_->mSprite2d_.mPosition_.z = position[2];
    }

    if (ImGui::SliderFloat3("Rotation##Model", rotation, -10.f, 10.f, "%.2f", 0.1f)) {
        mpScene_->mSprite2d_.mRotation_.x = rotation[0];
        mpScene_->mSprite2d_.mRotation_.y = rotation[1];
        mpScene_->mSprite2d_.mRotation_.z = rotation[2];
    }

    if (ImGui::SliderFloat3("Scale##Model", scale, -10.f, 10.f, "%.2f", 0.1f)) {
        mpScene_->mSprite2d_.mScale_.x = scale[0];
        mpScene_->mSprite2d_.mScale_.y = scale[1];
        mpScene_->mSprite2d_.mScale_.z = scale[2];
    }
    */
    if (ImGui::Button("Back")) {
        mpScene_->getApp()->setScene(new MenuScene(mpScene_->getApp()));
    }
    ImGui::End();
}