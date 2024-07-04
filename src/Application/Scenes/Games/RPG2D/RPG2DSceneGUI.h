#pragma once
#include "ImGuiComponent.h"

namespace rpg_2d {
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
         * @param theScene The scene this gui is for
         */
        RPG2DSceneGUI(RPG2DScene& theScene);

        /** Destructor */
        ~RPG2DSceneGUI();

        /** Build the GUI ImGui components every frame */
        void buildImGui() override;
    };

} // namespace rpg_2d