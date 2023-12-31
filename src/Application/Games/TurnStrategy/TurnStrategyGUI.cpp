#include "App.h"
#include "TurnStrategyGUI.h"
#include "TurnStrategyScene.h"

namespace TurnStrategy {
    TurnStrategyGUI::TurnStrategyGUI(TurnStrategyScene& theScene)
        : mScene_(theScene) {
        mVSyncEnabled_ =  mScene_.getApp().getWindow().getGLFWSwapInterval();
        mVolume_ = mScene_.getApp().getAudioManger().getGain();
        mCameraMode_ = static_cast<int>(mScene_.getFocusCamera()->getMode());
    }

    TurnStrategyGUI::~TurnStrategyGUI() {}

    void TurnStrategyGUI::buildImGui() {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
        ImGui::Begin("Settings");
        if (ImGui::Button("Back")) {
            mScene_.getApp().setScene(new GamesScene(mScene_.getApp()));
            mScene_.setRemove(true);
        }
        ImGui::Text("Turn Based Strategy Scene 1.0");
        ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));
        if (ImGui::Checkbox("vSync", &mVSyncEnabled_)) {
            mScene_.getApp().getWindow().setVSync(mVSyncEnabled_);
        }
        if (ImGui::SliderFloat("Volume", &mVolume_, 0.f, 1.f)) {
            mScene_.getApp().getAudioManger().setGain(mVolume_);
        }

        ImGui::Text("Camera");
        buildCameraSection();
        ImGui::Separator();

        ImGui::Text("Turn: %d", mScene_.getGame().getCurrentTurn());
        if (ImGui::Button("Next Turn")) {
            mScene_.getGame().nextTurn();
        }

        ImGui::Text("Selected Unit:");
        Entity* selectedEntity = mScene_.getGame().getSelectedEntity();

        if (selectedEntity != nullptr && dynamic_cast<Unit*>(selectedEntity)) {
            ImGui::Text(dynamic_cast<Unit*>(selectedEntity)->getName().c_str());

            float entityPosition[3] = {
                selectedEntity->getPosition().x,
                selectedEntity->getPosition().y,
                selectedEntity->getPosition().z
            };

            ImGui::SliderFloat3("Position", entityPosition, -10, 10);
        }

        if (selectedEntity != nullptr) {
            if (dynamic_cast<Unit*>(selectedEntity)) {
                // Unit options
                ImGui::Text("Unit:");
                ImGui::Text("Moves: %d", dynamic_cast<Unit*>(selectedEntity)->getMoves());

                bool canMoves = dynamic_cast<Unit*>(selectedEntity)->getMoves() > 0;
                bool canSettle = dynamic_cast<Unit*>(selectedEntity)->canSettle();
                ImGui::BeginDisabled(!canMoves || !canSettle); 
                if (ImGui::Button("Settle")) {
                    glm::ivec2 position = {
                      static_cast<int>(std::round(selectedEntity->getPosition().x)),
                      static_cast<int>(std::round(selectedEntity->getPosition().y))  
                    };
                    LOG_I("Create Settlement at %d %d", position.x, position.y);
                    dynamic_cast<Unit*>(selectedEntity)->doAction(1);
                    mScene_.getGame().spawnSettlement(position);
                }
                ImGui::EndDisabled();
            } else if (dynamic_cast<Settlement*>(selectedEntity)) {
                // Settlement options
                int population = dynamic_cast<Settlement*>(selectedEntity)->getPopulation();
                ImGui::Text("Settlement: %s", dynamic_cast<Settlement*>(selectedEntity)->getName().c_str());
                ImGui::Text("Population: %d", population);

                bool canSpawn = dynamic_cast<Settlement*>(selectedEntity)->canSpawnUnit();
                // TODO check that there are no units on the tile
                ImGui::BeginDisabled(!canSpawn); 
                if (ImGui::Button("Spawn Unit")) {
                    glm::ivec2 position = {
                      static_cast<int>(std::round(selectedEntity->getPosition().x)),
                      static_cast<int>(std::round(selectedEntity->getPosition().y))  
                    };
                    LOG_I("Spawn unit at %d %d", position.x, position.y);
                    mScene_.getGame().spawnUnit(position);
                    dynamic_cast<Settlement*>(selectedEntity)->setPopulation(dynamic_cast<Settlement*>(selectedEntity)->getPopulation() - 1);
                }
                ImGui::EndDisabled();

                bool canAddTerritory = dynamic_cast<Settlement*>(selectedEntity)->getPopulation() > dynamic_cast<Settlement*>(selectedEntity)->getSize();
                ImGui::BeginDisabled(!canAddTerritory); 
                if (ImGui::Button("Add Territory")) {
                    mScene_.getGame().addTerritoryMode = true;
                }
                ImGui::EndDisabled();
            }
        }

        ImGui::End();
    }

    void TurnStrategyGUI::buildCameraSection(){
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

} // namespace TurnStrategy