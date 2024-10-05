// forward declare
#include "App.h"
#include "VesselsScene.h"
// class
#include "VesselsSceneGUI.h"


#include <iostream>

namespace vessels {
    VesselsSceneGUI::VesselsSceneGUI(VesselsScene& theScene)
        : mScene_(theScene) {
        mVolume_ = mScene_.getApp().getAudioManger().getGain();
    }

    VesselsSceneGUI::~VesselsSceneGUI() {}

    void VesselsSceneGUI::buildImGui() {
        VesselsGame& game = mScene_.getGame();
        VesselsGame::GameState state = game.getGameState();

        if (state == VesselsGame::GameState::START) {
            buildStartPage();
        } else if (state == VesselsGame::GameState::MENU_SETTINGS) {
            buildSettingsPage();
        } else if (state == VesselsGame::GameState::SOUL_SELECT) {
            buildSoulSelectionPage();
        }  else if (state == VesselsGame::GameState::COSMOS_SELECTION) {
            buildCosmosSelectionPage();
        }  else if (state == VesselsGame::GameState::CORPOREAL_REALM) {
            buildGameHUD();
        } else if (state == VesselsGame::GameState::SOUL_REALM) {
            buildSoulRealmPage();
        }

        buildDevMenu();
    }

    void VesselsSceneGUI::buildCameraSection() {
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

    void VesselsSceneGUI::buildDevMenu() {
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);


        ImGui::Begin("Settings");
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 0.40f));
        if (ImGui::Button("Back")) {
            mScene_.getApp().setScene(new GamesScene(mScene_.getApp()));
            mScene_.setRemove(true);
        }
        ImGui::PopStyleColor();
        ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));
        buildCameraSection();
        ImGui::End();
    }
    
    void VesselsSceneGUI::buildStartPage() {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(800, 600));

        ImGui::Begin("Start", NULL, window_flags);

        // Text and buttons
        const char* text = "Vessels";
        ImVec2 textSize = ImGui::CalcTextSize(text);

        // Button dimensions
        float buttonWidth = 100.0f;
        float buttonHeight = ImGui::GetFrameHeight(); // Gets the default button height

        // Calculate total height (text + button height + optional padding)
        float totalHeight = textSize.y + buttonHeight * 3 + 20.0f * 2; // Two buttons + padding

        // Calculate vertical position to center the block
        float startY = (600 - totalHeight) * 0.5f;

        // Set cursor position to center the text horizontally and vertically as a block
        ImGui::SetCursorPosX((800 - textSize.x) * 0.5f);
        ImGui::SetCursorPosY(startY);

        // Draw centered text
        ImGui::Text("%s", text);

        // Add some spacing between the text and buttons
        ImGui::Dummy(ImVec2(0.0f, 10.0f));  // Vertical padding

        // Center buttons
        float buttonPosX = (800 - buttonWidth) * 0.5f;

        // First button
        ImGui::SetCursorPosX(buttonPosX);
        if (ImGui::Button("Start", ImVec2(buttonWidth, buttonHeight))) {
            // Button 1 action
            mScene_.getGame().setState(VesselsGame::GameState::SOUL_SELECT);
        }

        // Optional spacing between buttons
        ImGui::Dummy(ImVec2(0.0f, 5.0f));  // Vertical padding between buttons

        // Second button
        ImGui::SetCursorPosX(buttonPosX);
        if (ImGui::Button("Settings", ImVec2(buttonWidth, buttonHeight))) {
            // Button 2 action
            mScene_.getGame().setState(VesselsGame::GameState::MENU_SETTINGS);
        }

        // Optional spacing between buttons
        ImGui::Dummy(ImVec2(0.0f, 5.0f));  // Vertical padding between buttons

        // Second button
        ImGui::SetCursorPosX(buttonPosX);
        if (ImGui::Button("Quit", ImVec2(buttonWidth, buttonHeight))) {
            // Button 2 action
            mScene_.getApp().setScene(new GamesScene(mScene_.getApp()));
            mScene_.setRemove(true);
        }

        ImGui::End();
    }

    void VesselsSceneGUI::buildSettingsPage() {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(800, 600));

        ImGui::Begin("Settings", NULL, window_flags);

        // Text and buttons
        const char* text = "Settings";
        ImVec2 textSize = ImGui::CalcTextSize(text);

        // Button dimensions
        float buttonWidth = 100.0f;
        float buttonHeight = ImGui::GetFrameHeight(); // Gets the default button height

        // Calculate total height (text + button height + optional padding)
        float totalHeight = textSize.y + buttonHeight * 3 + 20.0f * 2; // Two buttons + padding

        // Calculate vertical position to center the block
        float startY = (600 - totalHeight) * 0.5f;

        // Set cursor position to center the text horizontally and vertically as a block
        ImGui::SetCursorPosX((800 - textSize.x) * 0.5f);
        ImGui::SetCursorPosY(startY);

        // Draw centered text
        ImGui::Text("%s", text);

        // Add some spacing between the text and buttons
        ImGui::Dummy(ImVec2(0.0f, 10.0f));  // Vertical padding

        // Center buttons
        float buttonPosX = (800 - buttonWidth) * 0.5f;

        // Optional spacing between buttons
        ImGui::Dummy(ImVec2(0.0f, 5.0f));  // Vertical padding between buttons

        // Adjust slider width
        float sliderWidth = 200.0f; // Set the desired slider width
        ImGui::SetCursorPosX((800 - sliderWidth) * 0.5f); // Center the slider
        ImGui::PushItemWidth(sliderWidth); // Set slider width

        // Slider
        if (ImGui::SliderFloat("Volume", &mVolume_, 0.f, 1.f)) {
            mScene_.getApp().getAudioManger().setGain(mVolume_);
        }


        ImGui::SetCursorPosX(buttonPosX);
        if (ImGui::Button("Back##MenuSetting")) {
            std::cout << "BACK CLICKED" << std::endl;
            mScene_.getGame().setState(VesselsGame::GameState::START);
        }

        ImGui::End();
    }

    void VesselsSceneGUI::buildSoulSelectionPage() {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(800, 600));

        ImGui::Begin("Soul Selection", NULL, window_flags);

        // Text and buttons
        const char* text = "Souls";
        ImVec2 textSize = ImGui::CalcTextSize(text);

        // Button dimensions
        float buttonWidth = 100.0f;
        float buttonHeight = ImGui::GetFrameHeight(); // Gets the default button height

        // Calculate total height (text + button height + optional padding)
        float totalHeight = textSize.y + buttonHeight * 3 + 20.0f * 2; // Two buttons + padding

        // Calculate vertical position to center the block
        float startY = (600 - totalHeight) * 0.5f;

        // Set cursor position to center the text horizontally and vertically as a block
        ImGui::SetCursorPosX((800 - textSize.x) * 0.5f);
        ImGui::SetCursorPosY(startY);

        // Draw centered text
        ImGui::Text("%s", text);

        // Add some spacing between the text and buttons
        ImGui::Dummy(ImVec2(0.0f, 10.0f));  // Vertical padding

        // Center buttons
        float buttonPosX = (800 - buttonWidth) * 0.5f;

        // First button
        ImGui::SetCursorPosX(buttonPosX);
        if (ImGui::BeginListBox("##Souls", ImVec2(100, ImGui::GetTextLineHeightWithSpacing() * 5))) {
            for (unsigned int i = 0; i < tempSouls.size(); ++i) {
                std::string tempName = tempSouls[i];
                if (ImGui::Selectable(tempName.c_str(), false)) {}
            }
            ImGui::EndListBox();
        }

        // Optional spacing between buttons
        ImGui::Dummy(ImVec2(0.0f, 5.0f));  // Vertical padding between buttons

        // Second button
        ImGui::SetCursorPosX(buttonPosX);
        if (ImGui::Button("Abandon##SoulSelect")) {}
        ImGui::SameLine();
        static bool showPopUp = false;

        if (ImGui::Button("New##SoulSelect")) {
            showPopUp = true;
        }

        // Optional spacing between buttons
        ImGui::Dummy(ImVec2(0.0f, 5.0f));  // Vertical padding between buttons

        // Second button
        ImGui::SetCursorPosX(buttonPosX);
        if (ImGui::Button("Back##SoulSelect")) {
            mScene_.getGame().setState(VesselsGame::GameState::START);
        }
        // Place "Start" button on the same line as "Back" button
        ImGui::SameLine();
        if (ImGui::Button("Start##SoulSelect")) {
            mScene_.getGame().setState(VesselsGame::GameState::COSMOS_SELECTION);
        }

        if (showPopUp) {
            ImGui::OpenPopup("My Modal Window");
            showPopUp = false; // Reset the flag to prevent reopening the popup repeatedly
        }

        // Open the modal popup
        if (ImGui::BeginPopupModal("My Modal Window", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("This is a modal window.");

            // Modal actions, e.g., Close or OK buttons
            if (ImGui::Button("OK")) {
                // Close the modal window when the button is clicked
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                // Close the modal window when Cancel is clicked
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup(); // End the modal popup
        }

        ImGui::End();
    }

    void VesselsSceneGUI::buildSoulBuildModal() {
        if (ImGui::Button("Name##SoulBuild")) {}
        if (ImGui::Button("Color##SoulBuild")) {}
        if (ImGui::Button("Cancel##SoulBuild")) {}
        if (ImGui::Button("Create##SoulBuild")) {}
    }

    void VesselsSceneGUI::buildCosmosSelectionPage() {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(800, 600));

        ImGui::Begin("Cosmos Selection", NULL, window_flags);

        // Text and buttons
        const char* text = "Cosmos";
        ImVec2 textSize = ImGui::CalcTextSize(text);

        // Button dimensions
        float buttonWidth = 100.0f;
        float buttonHeight = ImGui::GetFrameHeight(); // Gets the default button height

        // Calculate total height (text + button height + optional padding)
        float totalHeight = textSize.y + buttonHeight * 3 + 20.0f * 2; // Two buttons + padding

        // Calculate vertical position to center the block
        float startY = (600 - totalHeight) * 0.5f;

        // Set cursor position to center the text horizontally and vertically as a block
        ImGui::SetCursorPosX((800 - textSize.x) * 0.5f);
        ImGui::SetCursorPosY(startY);

        // Draw centered text
        ImGui::Text("%s", text);

        // Add some spacing between the text and buttons
        ImGui::Dummy(ImVec2(0.0f, 10.0f));  // Vertical padding

        // Center buttons
        float buttonPosX = (800 - buttonWidth) * 0.5f;

        // First button
        ImGui::SetCursorPosX(buttonPosX);
        if (ImGui::BeginListBox("##CosmosSelect", ImVec2(100, ImGui::GetTextLineHeightWithSpacing() * 5))) {
            for (unsigned int i = 0; i < tempSouls.size(); ++i) {
                std::string tempName = tempSouls[i];
                if (ImGui::Selectable(tempName.c_str(), false)) {}
            }
            ImGui::EndListBox();
        }

        ImGui::SetCursorPosX(buttonPosX);
        if (ImGui::Button("Abandon##SoulSelect")) {}
        ImGui::SameLine();
        static bool showPopUp = false;

        if (ImGui::Button("New##SoulSelect")) {
            showPopUp = true;
        }

        // Optional spacing between buttons
        ImGui::Dummy(ImVec2(0.0f, 5.0f));  // Vertical padding between buttons

        // Second button
        ImGui::SetCursorPosX(buttonPosX);
        if (ImGui::Button("Back##CosmosSelect")) {
            mScene_.getGame().setState(VesselsGame::GameState::SOUL_SELECT);
        }
        ImGui::SameLine();
        if (ImGui::Button("Join##CosmosSelect")) {
            mScene_.getGame().setState(VesselsGame::GameState::CORPOREAL_REALM);
        }

        ImGui::End();
    }

    void VesselsSceneGUI::buildGameHUD() {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(800, 600));
        ImGui::Begin("HUD", NULL, window_flags);
        ImGui::Text("Health##Game");
        ImGui::Text("Map##Game");
        ImGui::Text("Inventory##Game");
        if (ImGui::Button("Die##Game")) {
            mScene_.getGame().setState(VesselsGame::GameState::SOUL_REALM);
        }
        ImGui::End();
    }

    void VesselsSceneGUI::buildGameModal() {
        if (ImGui::Button("Settings##GameSetting")) {}
        if (ImGui::Button("Quit##GameSetting")) {}
    }

    void VesselsSceneGUI::buildSoulRealmPage() {
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoBackground;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(800, 600));

        ImGui::Begin("Lives", NULL, window_flags);

        // Text and buttons
        const char* text = "Lives";
        ImVec2 textSize = ImGui::CalcTextSize(text);

        // Button dimensions
        float buttonWidth = 100.0f;
        float buttonHeight = ImGui::GetFrameHeight(); // Gets the default button height

        // Calculate total height (text + button height + optional padding)
        float totalHeight = textSize.y + buttonHeight * 3 + 20.0f * 2; // Two buttons + padding

        // Calculate vertical position to center the block
        float startY = (600 - totalHeight) * 0.5f;

        // Set cursor position to center the text horizontally and vertically as a block
        ImGui::SetCursorPosX((800 - textSize.x) * 0.5f);
        ImGui::SetCursorPosY(startY);

        // Draw centered text
        ImGui::Text("%s", text);

        // Add some spacing between the text and buttons
        ImGui::Dummy(ImVec2(0.0f, 10.0f));  // Vertical padding

        // Center buttons
        float buttonPosX = (800 - buttonWidth) * 0.5f;

        // First button
        ImGui::SetCursorPosX(buttonPosX);
        if (ImGui::BeginListBox("##Lives", ImVec2(100, ImGui::GetTextLineHeightWithSpacing() * 5))) {
            for (unsigned int i = 0; i < tempSouls.size(); ++i) {
                std::string tempName = tempSouls[i];
                if (ImGui::Selectable(tempName.c_str(), false)) {}
            }
            ImGui::EndListBox();
        }

        // Optional spacing between buttons
        ImGui::Dummy(ImVec2(0.0f, 5.0f));  // Vertical padding between buttons

        // Second button
        ImGui::SetCursorPosX(buttonPosX);
        ImGui::Text("Details##SoulRealm");
        ImGui::SetCursorPosX(buttonPosX);

        if (ImGui::Button("Leave##SoulRealm")) {
            mScene_.getGame().setState(VesselsGame::GameState::COSMOS_SELECTION);
        }
        ImGui::SameLine();
        if (ImGui::Button("Reincarnate##SoulRealm")) {
            mScene_.getGame().setState(VesselsGame::GameState::CORPOREAL_REALM);
        }

        ImGui::End();
    }

} // namespace vessels