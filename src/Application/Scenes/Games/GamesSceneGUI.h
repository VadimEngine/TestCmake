#pragma once
#include "ImGuiComponent.h"

// Forward declare Scene
class GamesScene;

class GamesSceneGUI : public ImGuiComponent {
private:
    /** The Scene this GUI is for */
    GamesScene& mScene_;

public:
    /** 
     * Constructor
     * \param theScene The scene this gui is for
     */
    GamesSceneGUI(GamesScene& theScene);

    /** Destructor */
    ~GamesSceneGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;
};