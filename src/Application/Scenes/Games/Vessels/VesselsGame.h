#pragma once
// standard lib
#include <vector>
// third party
// project
#include "Entity.h"
#include "Cosmos.h"
#include "Player.h"
#include "Soul.h"
#include "InputHandler.h"
#include "CameraController.h"


// forward declare App
class App;

namespace vessels {
    // forward declare Scene
    class VesselsScene;

    class VesselsGame {
    public:

        enum class GameState {
            START, MENU_SETTINGS, SOUL_SELECT, COSMOS_SELECTION, CORPOREAL_REALM, SOUL_REALM 
        };

        // game states to control the GUI

        VesselsGame(VesselsScene& scene);

        ~VesselsGame();

        /**
         * Update Game
         * @param dt Time since last update
         */
        void update(const float dt);

        /**
         * Render Game
         * @param renderer Rendering Renderer
         */
        void render(Renderer& renderer);

        /**
         * Update the game based on key inputs// TODO SHOULD THIS BE PRIVATE?
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

        GameState getGameState();

        VesselsScene& getScene();

        void setState(GameState newState);

    private:
        VesselsScene& mScene_;
        // Player
        std::unique_ptr<Player> mpPlayer_;
        // Cosmos
        // Environment
        std::vector<std::unique_ptr<Entity>> mEntities_;

        GameState mState_ = GameState::START;

        InputHandler& mInputHandler_;

        CameraController mCameraController_;


    };

} // namespace vessels