#pragma once
#include "Entity.h"
#include "ModelRenderable.h"

namespace Pong {
    class Ball : public Entity {
    private:
        /** Inital ball speed*/
        float mInitalBallSpeed_ = 4.f;
        /** Circle plane model*/
        Model mCircleModel_;

    public:
        /** Constructor */
        Ball();

        /** Destructor */
        ~Ball();

        /**
         * Update the Ball
         * \param dt time since last update
         */
        void update(float dt) override;

        /** Start the ball movement */
        void start(const glm::vec3& dir);

        /** Get the current speed of the ball*/
        float getSpeed();

        /** Set the speed of the ball */
        void setSpeed(float newSpeed);

        /** Rest the ball position and velocity */
        void reset();
    };
} // namespace Pong