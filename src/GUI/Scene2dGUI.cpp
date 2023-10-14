#include "App.h"
#include "Scene2d.h"
#include "Scene2dGUI.h"

Scene2dGUI::Scene2dGUI(Scene2d& theScene) 
    : mScene_(theScene) {
    mVSyncEnabled_ =  mScene_.getApp().getWindow().getGLFWSwapInterval();
    mCameraMode_ = static_cast<int>(mScene_.getFocusCamera()->getMode());
}

Scene2dGUI::~Scene2dGUI() {}

void Scene2dGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings");
    ImGui::Text("Scene 2D");
    if (ImGui::Button("Back")) {
        mScene_.getApp().setScene(new MenuScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));

    if (ImGui::Checkbox("vSync", &mVSyncEnabled_)) {
        mScene_.getApp().getWindow().setVSync(mVSyncEnabled_);
    }
    ImGui::Separator();
    // TODO sprite position and rotation

    ImGui::Text("Camera");
    ImGui::Text("Camera Mode");
    if (ImGui::RadioButton("Perspective", &mCameraMode_, 0)) {
        mScene_.getFocusCamera()->setMode(static_cast<Camera::CameraMode>(mCameraMode_));
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Orthogonal", &mCameraMode_, 1)) {
        mScene_.getFocusCamera()->setMode(static_cast<Camera::CameraMode>(mCameraMode_));
    }

    ImGui::Text("Camera Movement");
    glm::vec3 camPosition = mScene_.getFocusCamera()->getPosition();
    ImGui::Text(
        "Position: %.2f %.2f %.2f",
        camPosition.x,
        camPosition.y,
        camPosition.z
    );
    glm::vec3 camForward = mScene_.getFocusCamera()->getForward();
    ImGui::Text(
        "Direction: %.2f %.2f %.2f",
        camForward.x,
        camForward.y,
        camForward.z
    );
    ImGui::Text(
        "FOV: %.2f",
        mScene_.getFocusCamera()->getFOV()
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
    ImGui::End();
}