#pragma once
#include "ImGuiComponent.h"

namespace pong {
    // Forward declare Scene
    class PongScene;

    class PongSceneGUI : public ImGuiComponent {
    public:
        /**
         * Constructor
         * @param theScene The scene this gui is for
         */
        PongSceneGUI(PongScene& theScene);

        /** Destructor */
        ~PongSceneGUI();

        /** Build the GUI ImGui components every frame */
        void buildImGui() override;
        
    private:
        /** The Scene this GUI is for */
        PongScene& mScene_;
        /** If the GUI is set to enable VSync */
        bool mVSyncEnabled_;
        /** Volume this gui applies */
        float mVolume_;
    };

} // namespace pong