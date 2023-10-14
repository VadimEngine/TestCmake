#pragma once
#include "ImGuiComponent.h"

// Forward declare Scene
class AssimpScene;

class AssimpGUI: public ImGuiComponent {
private:
    /** The Scene this GUI is for */
    AssimpScene& mScene_;

    /** The Entity index selected from the Entity List */
    int mSelectedEntityIndex_ = 0;

    /** The Renderable index selected from the Entity List */
    int mSelectedRenderableIndex_ = 0;
    
public:
    /** 
     * Constructor
     * \param theScene The scene this gui is for
     */
    AssimpGUI(AssimpScene& theScene);

    /** Destructor */
    ~AssimpGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;
};