#pragma once
#include "ImGuiComponent.h"

namespace menu_scene {
    // Forward declare Scene
    class MenuScene;

    class MenuGUI: public ImGuiComponent {
    private:
        /** The Scene this GUI is for */
        MenuScene& mScene_;
    public:
        /**
         * Constructor
         * @param theScene The scene this gui is for
         */
        MenuGUI(MenuScene& theScene);

        /** Destructor */
        ~MenuGUI();

        /** Build the GUI ImGui components every frame */
        void buildImGui() override;
    };
} // namespace menu_scene