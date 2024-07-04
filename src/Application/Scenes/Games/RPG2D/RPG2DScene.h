#pragma once
#include "Scene.h"
#include "RPG2DSceneGUI.h"
#include "RPG2DGame.h"

// Forward Declare App
class App;

namespace rpg_2d {
    class RPG2DScene : public Scene {
    private:
        RPG2DSceneGUI mGui_;

        RPG2DGame mGame_;

    public:
        RPG2DScene(App& theApp);

        /** Destructor */
        ~RPG2DScene();

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

        void onMousePress(const InputHandler::MouseEvent& mouseEvent);

    };

} // namespace rpg_2d 