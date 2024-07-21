#pragma once
// project
#include "Scene.h"
#include "TurnStrategyGame.h"
#include "TurnStrategyGUI.h"

// Forward Declare App
class App;

namespace turn_strategy {
    class TurnStrategyScene : public Scene {
    public:
        /**
         * Constructor
         * @param theApp Parent app handling this Scene
         */
        TurnStrategyScene(App& theApp);

        /** Destructor */
        ~TurnStrategyScene();

        /** Load/build resources for this Scene */
        void assembleResources() override;

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
         * On Mouse button press handler
         * @param mouseEvent Mouse event details
         */
        void onMousePress(const InputHandler::MouseEvent& mouseEvent) override;

        /**
         * On Mouse Button release handler
         * @param mouseEvent Mouse event details
         */
        void onMouseRelease(const InputHandler::MouseEvent& mouseEvent) override;

        /**
         * On wheel handler
         * @param mouseEvent Mouse event details
         */
        void onMouseWheel(const InputHandler::MouseEvent& mouseEvent) override;

        /** Get reference to the game handler in this scene */
        TurnStrategyGame& getGame();

    private:
        /** GUI for this scene */
        TurnStrategyGUI mGui_;
        /** Game logic handler */
        std::unique_ptr<TurnStrategyGame> mpGame_;
    };

} // namespace turn_strategy