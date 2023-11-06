#pragma once
#include "Entity.h"
#include "ModelRenderable.h"

namespace Pong {
    class Paddle : public Entity {
    private:
        /** Paddle upper position bound */ 
        float mMaxHeight_ = 5.f;
        /** Paddle lower position bound */ 
        float mMinHeight_ = -5.f;
        /** X position of the paddle*/
        float mXPosition_ = -5.f;
        /** Movement speed of the paddle*/
        float mMovementSpeed_ = 5.f;
        /** Rectangle model for rendering */
        Model mRectModel_;

    public:
        /**
         *  Constructor
         * \param xPos X position of paddle
         * \param maxY Upper position bound
         * \param minY Lower position bound
         */
        Paddle(float xPos, float maxY, float minY);
        
        /** Destructor */
        ~Paddle();

        /**
         * Update paddle
         * \param dt Time since last update
         */
        void update(float dt) override;

        /** Rest the paddle position */
        void reset();

        /** Move up at the paddle's speed */
        void moveUp(float dt);

        /** Move down at the paddle's speed */
        void moveDown(float dt);
        
    };
} // namespace Pong