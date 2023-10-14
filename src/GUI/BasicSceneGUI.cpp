#include "App.h"
#include "BasicScene.h"
#include "BasicSceneGUI.h"

BasicSceneGUI::BasicSceneGUI(BasicScene& theScene)
    : mScene_(theScene) {
        mCameraMode_ = static_cast<int>(mScene_.getFocusCamera()->getMode());
}

BasicSceneGUI::~BasicSceneGUI() {}

void BasicSceneGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings");
    if (ImGui::Button("Back")) {
        mScene_.getApp().setScene(new MenuScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    ImGui::Text("Basic Scene");
    ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));

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

    ImGui::Text("Entity");

    if (ImGui::BeginListBox("##Entities")) {
        for (unsigned int i = 0; i < mScene_.getEntities().size(); i++) {
            std::string tempName = "Entity " + std::to_string(i);
            if (ImGui::Selectable(tempName.c_str(), i == mSelectedEntityIndex_)) {
                mSelectedEntityIndex_ = i;
            }
        }
        ImGui::EndListBox();
    }

    if (mSelectedEntityIndex_ < mScene_.getEntities().size()) {
        Entity* selectedEntity = mScene_.getEntities()[mSelectedEntityIndex_]; 

        float entityPosition[3] = {
            selectedEntity->getPosition().x,
            selectedEntity->getPosition().y,
            selectedEntity->getPosition().z
        };
        float entityRotation[3] = {
            selectedEntity->getRotation().x,
            selectedEntity->getRotation().y,
            selectedEntity->getRotation().z
        };
        float entityScale[3] = {
            selectedEntity->getScale().x,
            selectedEntity->getScale().y,
            selectedEntity->getScale().z
        };

        if (ImGui::SliderFloat3("Position##Entity", entityPosition, -10.f, 10.f, "%.2f")) {
            selectedEntity->setPosition({
                entityPosition[0],
                entityPosition[1],
                entityPosition[2]
            });
        }

        if (ImGui::SliderFloat3("Rotation##Entity", entityRotation, -10.f, 10.f, "%.2f")) {
            selectedEntity->setRotation({
                entityRotation[0],
                entityRotation[1],
                entityRotation[2]
            });
        }

        if (ImGui::SliderFloat3("Scale##Entity", entityScale, -10.f, 10.f, "%.2f")) {
            selectedEntity->setScale({
                entityScale[0],
                entityScale[1],
                entityScale[2]
            });
        }

        ImGui::Text("Renderable Components");

        if (ImGui::BeginListBox("##Renderables")) {
            for (unsigned int i = 0; i <selectedEntity->getRenderableComponents().size(); i++) {
                std::string tempName = "Renderable " + std::to_string(i);
                if (ImGui::Selectable(tempName.c_str(), i == mSelectedRenderableIndex_)) {
                    mSelectedRenderableIndex_ = i;
                }
            }
            ImGui::EndListBox();
        }

        if (mSelectedRenderableIndex_ < selectedEntity->getRenderableComponents().size()) {
            IRenderable* selectedRenderable = selectedEntity->getRenderableComponents()[mSelectedRenderableIndex_];

            float renderablePosition[3] = {
                selectedRenderable->getPosition().x,
                selectedRenderable->getPosition().y,
                selectedRenderable->getPosition().z
            };
            float renderableRotation[3] = {
                selectedRenderable->getRotation().x,
                selectedRenderable->getRotation().y,
                selectedRenderable->getRotation().z
            };
            float renderableScale[3] = {
                selectedRenderable->getScale().x,
                selectedRenderable->getScale().y,
                selectedRenderable->getScale().z
            };

            bool isEnabled = selectedRenderable->isEnabled();

            if  (ImGui::Checkbox("Enabled", &isEnabled)) {
                selectedRenderable->setEnabled(isEnabled);
            }

            if (ImGui::SliderFloat3("Position##Renderable", renderablePosition, -10.f, 10.f, "%.2f")) {
                selectedRenderable->setPosition({
                    renderablePosition[0],
                    renderablePosition[1],
                    renderablePosition[2]
                });
            }

            if (ImGui::SliderFloat3("Rotation##Renderable", renderableRotation, -10.f, 10.f, "%.2f")) {
                selectedRenderable->setRotation({
                    renderableRotation[0],
                    renderableRotation[1],
                    renderableRotation[2]
                });
            }

            if (ImGui::SliderFloat3("Scale##Renderable", renderableScale, -10.f, 10.f, "%.2f")) {
                selectedRenderable->setScale({
                    renderableScale[0],
                    renderableScale[1],
                    renderableScale[2]
                });
            }
        }
    }

    ImGui::End();
};