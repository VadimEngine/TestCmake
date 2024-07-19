#pragma once
#include "Entity.h"
#include "ModelRenderable.h"

namespace pong {
    class Paddle : public Entity {
    public:
        /**
         * Constructor
         * @param scene Scene this Entity is in
         * @param dimension Paddle size scale
         */
        Paddle(Scene& scene, glm::vec2 dimension);

        /** Destructor */
        ~Paddle();

        /**
         * Update paddle
         * 
         * @param dt Time since last update
         */
        void update(float dt) override;

        /** Rest the paddle position */
        void reset();

        /**
         * @brief Move up at the paddle's speed
         * 
         * @param dt Time since last update
         */
        void moveUp(float dt);

        /**
         * @brief Move down at the paddle's speed
         * 
         * @param dt Time since last update
         */
        void moveDown(float dt);

        /**
         * @brief Set the Default Position of the paddle when the game starts
         * 
         * @param newPosition x/y position
         */
        void setDefaultPosition(glm::vec2 newPosition);

    private:
        /** Default position of this paddle. Used for reset */
        glm::vec3 mDefaultPos_;
        /** Movement speed of the paddle*/
        float mMovementSpeed_ = 3.f;
    };
} // namespace pong