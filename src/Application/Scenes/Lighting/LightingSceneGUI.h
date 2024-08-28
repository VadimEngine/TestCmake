#pragma once
// project
#include "ImGuiComponent.h"

namespace lighting_scene {
    // Forward declare Scene
    class LightingScene;

    class LightingSceneGUI : public ImGuiComponent {
    public:
        /**
         * Constructor
         * @param theScene The scene this gui is for
         */
        LightingSceneGUI(LightingScene& theScene);

        /** Destructor */
        ~LightingSceneGUI();

        /** Build the GUI ImGui components every frame */
        void buildImGui() override;

    private:
        /** Build the section to list/control the camera of this scene */
        void buildCameraSection();

        /** Build the section to list/control the Entities of the Scene*/
        void buildEntitySection();

        void buildLightSourceSection();

        /** The Scene this GUI is for */
        LightingScene& mScene_;
        /** If the GUI is set to enable VSync */
        bool mVSyncEnabled_;
        /** The Camera Mode this GUI applies*/
        int mCameraMode_;
        /** The Entity index selected from the Entity List */
        int mSelectedEntityIndex_ = 0;
        /** The Renderable index selected from the Entity List */
        int mSelectedRenderableIndex_ = 0;
        /** The Light source select from the list of lights */
        int mSelectedLightIndex_ = 0;
        /** Current applied exposure */
        float mExposure_;
    };

} // namespace lighting_scene
