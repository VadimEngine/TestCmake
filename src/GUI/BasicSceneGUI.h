#pragma once
#include "ImGuiComponent.h"

// Forward declare Scene
class BasicScene;

class BasicSceneGUI: public ImGuiComponent {
private:
    /** The Scene this GUI is for */
    BasicScene& mScene_;

    /** The Camera Mode this GUI applies*/
    int mCameraMode_;

    /** The Entity index selected from the Entity List */
    int mSelectedEntityIndex_ = 0;

    /** The Renderable index selected from the Entity List */
    int mSelectedRenderableIndex_ = 0;

public:
    /** 
     * Constructor
     * \param theScene The scene this gui is for
     */
    BasicSceneGUI(BasicScene& theScene);
    
    /** Destructor */
    ~BasicSceneGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;
};