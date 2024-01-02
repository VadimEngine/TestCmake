#pragma once
#include "ImGuiComponent.h"

namespace TurnStrategy {

    // Forward declare Scene
    class TurnStrategyScene;

    class TurnStrategyGUI : public ImGuiComponent {
    private:
        /** The Scene this GUI is for */
        TurnStrategyScene& mScene_;

        /** If the GUI is set to enable VSync */
        bool mVSyncEnabled_;

        /** Volume this gui applies */
        float mVolume_;

        /** The Camera Mode this GUI applies*/
        int mCameraMode_;

    public:
        /** 
         * Constructor
         * \param theScene The scene this gui is for
         */
        TurnStrategyGUI(TurnStrategyScene& theScene);

        /** Destructor */
        ~TurnStrategyGUI();

        /** Build the GUI ImGui components every frame */
        void buildImGui() override;

        void buildCameraSection();
    };

} // namespace TurnStrateg