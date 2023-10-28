#include "App.h"
#include "PhysicsScene.h"
#include "PhysicsSceneGUI.h"

PhysicsSceneGUI::PhysicsSceneGUI(PhysicsScene& theScene)
    : mScene_(theScene) {
    mVSyncEnabled_ =  mScene_.getApp().getWindow().getGLFWSwapInterval();
    mCameraMode_ = static_cast<int>(mScene_.getFocusCamera()->getMode());
}

PhysicsSceneGUI::~PhysicsSceneGUI() {}

void PhysicsSceneGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings");
    if (ImGui::Button("Back")) {
        mScene_.getApp().setScene(new MenuScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    ImGui::Text("Physics Scene");
    ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));
    if (ImGui::Checkbox("vSync", &mVSyncEnabled_)) {
        mScene_.getApp().getWindow().setVSync(mVSyncEnabled_);
    }
    ImGui::Separator();

    if (ImGui::Checkbox("Running", &mSceneRunning_)) {
        mScene_.setRunning(mSceneRunning_);
    }

    // Camera control
    buildCameraSection();
    ImGui::Separator();
    // Entity control
    buildEntitySection();
    ImGui::End();
}

void PhysicsSceneGUI::buildCameraSection(){
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
}

void PhysicsSceneGUI::buildEntitySection() {
    ImGui::Text("Entities");

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
        // Display selected Entity details/controls
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
        float entityVelocity[3] = {
            selectedEntity->getVelocity().x,
            selectedEntity->getVelocity().y,
            selectedEntity->getVelocity().z
        };

        bool isAttractive = selectedEntity->getPhysicsComponent<RigidBodyComponent>()->isAttractive();

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

        if (ImGui::SliderFloat3("Velocity##Entity", entityVelocity, -10.f, 10.f, "%.2f")) {
            selectedEntity->setVelocity({
                entityVelocity[0],
                entityVelocity[1],
                entityVelocity[2]
            });
        }
        if (ImGui::Checkbox("Attractive###Entity", &isAttractive)) {
            selectedEntity->getPhysicsComponent<RigidBodyComponent>()->setAttractive(isAttractive);
        }

        if (mSelectedRenderableIndex_ < selectedEntity->getRenderableComponents().size()) {
            // Display selected Renderable details/controls
            BaseRenderable* selectedRenderable = selectedEntity->getRenderableComponents()[mSelectedRenderableIndex_];

            float renderableColor[4] = {
                selectedRenderable->getColor().r,
                selectedRenderable->getColor().g,
                selectedRenderable->getColor().b,
                selectedRenderable->getColor().a
            };

            if (ImGui::ColorEdit4("Color##Renderable", renderableColor)) {
                selectedRenderable->setColor({
                    renderableColor[0],
                    renderableColor[1],
                    renderableColor[2],
                    renderableColor[3]
                });
            }
        }
        if (ImGui::Button("Remove Entity")) {
            mScene_.getEntities().erase(mScene_.getEntities().begin() + mSelectedEntityIndex_);
        }
    }

    if (ImGui::Button("Add Entity")) {
        mScene_.addEntity();
    }
}
