#pragma once
// project
#include "ImGuiComponent.h"

namespace galaxy {

// Forward declare Scene
class GalaxyScene;

class GalaxySceneGUI : public ImGuiComponent {
public:
    /**
     * Constructor
     * @param theScene The scene this gui is for
     */
    GalaxySceneGUI(GalaxyScene& theScene);

    /** Destructor */
    ~GalaxySceneGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;

private:
    /** The Scene this GUI is for */
    GalaxyScene& mScene_;
    /** Applied running status to the scene*/
    bool mSceneRunning_ = true;
};

} // namespace galaxy