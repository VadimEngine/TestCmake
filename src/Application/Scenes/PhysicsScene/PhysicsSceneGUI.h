#pragma once
#include "ImGuiComponent.h"

// Forward declare Scene
class PhysicsScene;

class PhysicsSceneGUI : public ImGuiComponent {
private:
    /** The Scene this GUI is for */
    PhysicsScene& mScene_;

    /** If the GUI is set to enable VSync */
    bool mVSyncEnabled_;

    /** The Camera Mode this GUI applies*/
    int mCameraMode_;

    /** The Entity index selected from the Entity List */
    int mSelectedEntityIndex_ = 0;

    /** The Renderable index selected from the Entity List */
    int mSelectedRenderableIndex_ = 0;

    bool mSceneRunning_ = true;

public:
    /** 
     * Constructor
     * \param theScene The scene this gui is for
     */
    PhysicsSceneGUI(PhysicsScene& theScene);

    /** Destructor */
    ~PhysicsSceneGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;
    
private:
    /** Build the section to list/control the camera of this scene */
    void buildCameraSection();

    /** Build the section to list/control the Entities of the Scene*/
    void buildEntitySection();
};