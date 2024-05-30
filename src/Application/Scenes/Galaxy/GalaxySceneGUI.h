#pragma once
#include "ImGuiComponent.h"

namespace galaxy {

// Forward declare Scene
class GalaxyScene;

class GalaxySceneGUI : public ImGuiComponent {
private:
    /** The Scene this GUI is for */
    GalaxyScene& mScene_;

    bool mSceneRunning_ = true;

public:
    /** 
     * Constructor
     * \param theScene The scene this gui is for
     */
    GalaxySceneGUI(GalaxyScene& theScene);

    /** Destructor */
    ~GalaxySceneGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;
};

} // namespace galaxy