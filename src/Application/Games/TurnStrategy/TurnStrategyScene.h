#pragma once
#include "Scene.h"
#include "TurnStrategyGUI.h"
#include "TurnStrategyGame.h"

// Forward Declare App
class App;

namespace TurnStrategy {

    class TurnStrategyScene : public Scene {
    private:
        TurnStrategyGUI mGui_;

        TurnStrategyGame game;

    public:
        /**  
         * Constructor
         * \param theApp Parent app handling this Scene
         */
        TurnStrategyScene(App& theApp);

        /** Destructor */
        ~TurnStrategyScene();

        /** 
         * Update the Scene
         * \param dt Time since last update in seconds
         */
        void update(const float dt) override;

        /**
         * Render this scene
         * \param renderer Rendering helper
         */
        void render(Renderer& renderer) override;

        /** 
         * On keyboard key press handler
         * \param newColor key code for pressed key
         */
        void onKeyPress(unsigned int code) override;

        /** 
         * On keyboard key release handler
         * \param newColor key code for released key
         */
        void onKeyRelease(unsigned int code) override;

        /** 
         * On Mouse button press handler
         * \param mousePos Mouse Position at time of the event
         * \param mouseEvent Mouse event details
         */
        void onMousePress(const InputHandler::MouseEvent& mouseEvent) override;

        /** 
         * On Mouse Button release handler
         * \param mousePos Mouse Position at time of the event
         * \param mouseEvent Mouse event details
         */
        void onMouseRelease(const InputHandler::MouseEvent& mouseEvent) override;

        void onMouseWheel(const InputHandler::MouseEvent& mouseEvent) override;

        TurnStrategyGame& getGame();
    };

} // namespace TurnStrategy