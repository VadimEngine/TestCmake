#pragma once
#include "ImGuiComponent.h"

namespace RPG2D {
    // Forward declare Scene
    class RPG2DScene;

    class RPG2DSceneGUI : public ImGuiComponent {
    private:
        /** The Scene this GUI is for */
        RPG2DScene& mScene_;

        /** If the GUI is set to enable VSync */
        bool mVSyncEnabled_;

        /** Volume this gui applies */
        float mVolume_;

    public:
        /** 
         * Constructor
         * \param theScene The scene this gui is for
         */
        RPG2DSceneGUI(RPG2DScene& theScene);

        /** Destructor */
        ~RPG2DSceneGUI();

        /** Build the GUI ImGui components every frame */
        void buildImGui() override;
    };

} // namespace RPG2D