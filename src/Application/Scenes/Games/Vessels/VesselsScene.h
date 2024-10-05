#pragma once
// standard
#include <memory>
// third party
// project
#include "Scene.h"
#include "VesselsGame.h"
#include "VesselsSceneGUI.h"

class App;

namespace vessels {
    class VesselsScene : public Scene {
    public:
        VesselsScene(App& theApp);

        /** Destructor */
        ~VesselsScene();

        /**
         * Update the Scene
         * @param dt Time since last update in seconds
         */
        void update(const float dt) override;

        /**
         * Render this scene
         * @param renderer Rendering helper
         */
        void render(Renderer& renderer) override;

        /**
         * Render just the gui for this scene
         */
        void renderGUI() override;

        /**
         * On keyboard key press handler
         * @param newColor key code for pressed key
         */
        void onMousePress(const InputHandler::MouseEvent& mouseEvent) override;

        /**
         * @brief Loads and builds resources that are used for this scene
         */
        void assembleResources() override;

        VesselsGame& getGame();


    private:
        VesselsSceneGUI mGui_;

        std::unique_ptr<VesselsGame> mpGame_;
    };

} // namespace vessels