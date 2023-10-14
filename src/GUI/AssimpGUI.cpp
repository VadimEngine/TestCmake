#include "App.h"
#include "AssimpScene.h"
#include "AssimpGUI.h"

AssimpGUI::AssimpGUI(AssimpScene& theScene)
    :mScene_(theScene) {}

AssimpGUI::~AssimpGUI() {}

void AssimpGUI::buildImGui() {
    Camera* pCamera = mScene_.getFocusCamera();

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings");
    ImGui::Text("Assimp Scene");
    if (ImGui::Button("Back")) {
        mScene_.getApp().setScene(new MenuScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
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