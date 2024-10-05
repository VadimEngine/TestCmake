#pragma once
// project
#include "ImGuiComponent.h"

namespace vessels {
    // Forward declare Scene
    class VesselsScene;

    class VesselsSceneGUI: public ImGuiComponent {
    public:
        /**
         * Constructor
         * @param theScene The scene this gui is for
         */
        VesselsSceneGUI(VesselsScene& theScene);

        /** Destructor */
        ~VesselsSceneGUI();

        /** Build the GUI ImGui components every frame */
        void buildImGui() override;

    private:

        // build start page
        // build Soul selection page
        // build cosmos selection page
        // build game page
            // corporeal
            // soul

        void buildCameraSection();

        void buildDevMenu();

        void buildStartPage();

        void buildSettingsPage();

        void buildSoulSelectionPage();

        void buildSoulBuildModal();

        void buildCosmosSelectionPage();

        void buildGameHUD();

        void buildGameModal();

        void buildSoulRealmPage();


        /** The Scene this GUI is for */
        VesselsScene& mScene_;
        /** If the GUI is set to enable VSync */
        bool mVSyncEnabled_;
        /** The Camera Mode this GUI applies*/
        int mCameraMode_;

        float mVolume_;

        std::vector<std::string> tempSouls = {"One", "Two", "Three"};
    };

} // namespace vessels