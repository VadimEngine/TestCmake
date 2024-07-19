#pragma once
#include "Scene.h"
#include "PongSceneGUI.h"
#include "PongGame.h"

// Forward Declare App
class App;

namespace pong {
    class PongScene : public Scene {
    public:
        /**
         * Constructor
         * @param theApp Parent app handling this Scene
         */
        PongScene(App& theApp);

        /** Destructor */
        ~PongScene();

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

        /** Build/load resources for this scene */
        void assembleResources() override;

        /**
         * On keyboard key press handler
         * @param newColor key code for pressed key
         */
        void onKeyPress(unsigned int code) override;

        /**
         * On keyboard key release handler
         * @param newColor key code for released key
         */
        void onKeyRelease(unsigned int code) override;

        /**
         * @brief Get the game this scene is handling
         */
        PongGame& getGame();

    private:
        /** GUI for this Scene*/
        PongSceneGUI mGui_;
        /** Game logic handler */
        std::unique_ptr<PongGame> mpGame_;
    };

} // namespace pong