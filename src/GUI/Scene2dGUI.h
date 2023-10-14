#pragma once
#include "ImGuiComponent.h"
#include <vector>

// Forward declare Scene
class Scene2d;

class Scene2dGUI : public ImGuiComponent {
private:
    /** The Scene this GUI is for */
    Scene2d& mScene_;
    /** If the GUI is set to enable VSync */
    bool mVSyncEnabled_;
    /** The camera mode applied to the scene's focused camera */
    int mCameraMode_;

public:
    /** 
     * Constructor
     * \param theScene The scene this gui is for
     */
    Scene2dGUI(Scene2d& theScene);

    /** Destructor */
    ~Scene2dGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;
};