#pragma once
// project
#include "CameraController.h"
#include "InputHandler.h"
#include "MOB.h"
#include "Player.h"
#include "Renderer.h"

// forward declare App
class App;

namespace rpg_2d {
    // forward Scene
    class RPG2DScene;

    class RPG2DGame {
    public:
        RPG2DGame(RPG2DScene& scene, Camera& focusCamera);

        ~RPG2DGame();

        /**
         * Update Game
         * @param dt Time since last update
         */
        void update(const float dt);

        /**
         * Render Game
         * @param renderer Rendering Renderer
         * @param camera Camera to render relative to
         */
        void render(Renderer& renderer, Camera& camera);

        /**
         * Update the game based on key inputs
         * @param dt Time since last update
        */
        void handleKeyUpdate(float dt);

        /**
         * Update the game based on certain key pressed events
         * @param code Keycode of press key
         */
        void onKeyPress(unsigned int code);

        /**
         * Update the game based on certain key release events
         * @param code Keycode of released key
         */
        void onKeyRelease(unsigned int code);

        void onMousePress(const InputHandler::MouseEvent& mouseEvent);

    private:
        RPG2DScene& mScene_;
        App& mApp_;

        Player thePlayer;

        MOB theMOB;

        CameraController mCameraController_;

        InputHandler& mInputHandler_;
    };

} // namespace rpg_2d