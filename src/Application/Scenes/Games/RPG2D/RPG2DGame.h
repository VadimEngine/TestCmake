#pragma once
#include "Renderer.h"
#include "Player.h"
#include "MOB.h"
#include "InputHandler.h"
#include "CameraController.h"

// forward declare App, Scene
class App;
class RPG2DScene;

namespace rpg_2d {
    class RPG2DGame {
    private:
        RPG2DScene& mScene_;
        App& mApp_;
        
        Player thePlayer;

        MOB theMOB;

        CameraController mCameraController_;

        InputHandler& mInputHandler_;

    public:
        RPG2DGame(RPG2DScene& scene, Camera& focusCamera);

        ~RPG2DGame();

        /** 
         * Update Game
         * \param dt Time since last update
         */
        void update(const float dt);

        /** 
         * Render Game
         * \param renderer Rendering Renderer
         * \param camera Camera to render relative to
         */
        void render(Renderer& renderer, Camera& camera);

        /**
         * Update the game based on key inputs
         * \param dt Time since last update
        */
        void handleKeyUpdate(float dt);

        /** 
         * Update the game based on certain key pressed events
         * \param code Keycode of press key
         */
        void onKeyPress(unsigned int code);

        /** 
         * Update the game based on certain key release events
         * \param code Keycode of released key
         */
        void onKeyRelease(unsigned int code);

        void onMousePress(const InputHandler::MouseEvent& mouseEvent);
    };

} // namespace rpg_2d