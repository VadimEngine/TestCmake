#include "App.h"
#include "GamesSceneGUI.h"
#include "GamesScene.h"

GamesSceneGUI::GamesSceneGUI(GamesScene& theScene)
    : mScene_(theScene) {
}

GamesSceneGUI::~GamesSceneGUI() {}

void GamesSceneGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Games");
    if (ImGui::Button("Pong")) {
        mScene_.getApp().setScene(new Pong::PongScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    if (ImGui::Button("Turn-Based Strategy")) {
        mScene_.getApp().setScene(new TurnStrategy::TurnStrategyScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    if (ImGui::Button("Back")) {
        mScene_.getApp().setScene(new MenuScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    ImGui::End();
}