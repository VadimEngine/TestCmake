#pragma once
// standard lib
#include <array>
#include <vector>
// third party
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/normalize_dot.hpp>
// project
#include "Ball.h"
#include "InputHandler.h"
#include "ModelRenderable.h"
#include "Paddle.h"
#include "Renderer.h"

// forward declare App
class App;

namespace pong {

    // forward declare Scene
    class PongScene;

    class PongGame {
    public:
        /**
         * @brief Constructor
         * 
         * @param scene Scene this game is in
         */
        PongGame(PongScene& scene);

        /** Destructor*/
        ~PongGame();

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
         * Update the game based on key inputs
         * // TODO SHOULD THIS BE PRIVATE?
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

        /**
         * @brief Get the size of the Game board
         */
        glm::vec2 getBoardSize() const;

    private:
        /** Game states */
        enum class GameState {
            INITIAL, PLAYING, PAUSE, END
        };

        struct Properties {
            struct PaddleProp {
                float width = 5.0f;
                float height = 5.0f;
                float startX = 0;
                float startY = 0;
            };
            PaddleProp leftPaddle {.width = .1f, .height = .5f, .startX = -2.f + .1f/2, .startY = 0};
            PaddleProp rightPaddle {.width = .1f, .height = .5f, .startX = 2.f - .1f/2, .startY = 0};
            /** Ball radius */
            float ballRadius = .1f;
            /** Score for winning a Pong game*/
            int maxScore = 5;
            // TODO get from camera
            glm::vec2 boardSize {4, 3};
        };

        /** Resolve collisions to avoid overlapping */
        void handleEntityOverlap();

        /** Message displayed when Game is at inital state */
        static const std::string kInitalMsg;
        /** Message displayed when Game is paused */
        static const std::string kPauseMsg;
        /** Game displayed when game is over*/
        static const std::string kEndMsg;

        // Game properties
        Properties mProperties_;
        /** Scene this game is in */
        PongScene& mScene_;
        /** Parent App running this game*/
        App& mApp_;
        /** Left Paddle */
        std::array<std::unique_ptr<Paddle>, 2> mPaddles_;
        /** Game Ball */
        std::unique_ptr<Ball> mBall_;
        /** Entities rendered in this Game */
        std::vector<Entity*> mEntities_;
        /** Player scores */
        std::array<int, 2> mScores_ {0, 0};
        /** Track what the current game state is */
        GameState mCurrentState_ = GameState::INITIAL;
        /** Reference to input handler of parent App */
        InputHandler& mInputHandler_;
    };

} // namespace pong