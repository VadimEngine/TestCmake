#pragma once
#include "Renderer.h"
#include <vector>
#include "Entity.h"
#include "ModelRenderable.h"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/normalize_dot.hpp>
#include "InputHandler.h"
#include "Paddle.h"
#include "Ball.h"
#include "ImGuiComponent.h"

// forward declare App
class App;

namespace Pong {
    class PongGame {
    private:
        /** Game states */
        enum class GameState {
            INITIAL, PLAYING, PAUSE, END
        };

        /** Left Paddle*/
        Paddle mPaddleLeft_;
        /** Right Paddle*/
        Paddle mPaddleRight_;
        /** Game Ball */
        Ball mBall_;

        /** Entities rendered in this Game */
        std::vector<Entity*> mEntities_;

        /** Score for winning a Pong game*/
        int maxScore = 5;
        /** Tracking Left player score*/
        int leftScore = 0;
        /** Tracking Right player score */
        int rightScore = 0;

        /** Message displayed when Game is at inital state */
        std::string initalMsg = "Press Space to Begin";
        /** Message displayed when Game is paused */
        std::string pauseMsg = "Paused. Press Space to Resume";
        /** Game displayed when game is over*/
        std::string endMsg = "Game Over! Press Space to Continue";
        
        /** Track what the current game state is */
        GameState currentState = GameState::INITIAL;

        /** Parent App running this game*/
        App& mApp_;
        /** Reference to input handler of parent App */
        InputHandler& mInputHandler_;

    public:
        /** Constructor */
        PongGame(App& App);

        /** Destructor*/
        ~PongGame();

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

    private:
        /** Resolve collisions to avoid overlapping */
        void handleEntityOverlap();

        /** Check and enact collision actions between Entities */
        void handleEntityCollision(const float dt);
    };

} // namespace Pong