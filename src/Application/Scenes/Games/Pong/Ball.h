#pragma once
#include "Entity.h"
#include "ModelRenderable.h"

namespace pong {
    class Ball : public Entity {
    public:
        /**
         * @brief Constructor
         * 
         * @param scene Scene this ball is in
         * @param radius Ball radius
         */
        Ball(Scene& scene, float radius);

        /** Destructor */
        ~Ball();

        /**
         * Update the Ball
         * @param dt time since last update
         */
        void update(float dt) override;

        /** Start the ball movement */
        void start(const glm::vec3& dir);

        /** Get the current speed of the ball*/
        float getSpeed();

        /**
         * Set the speed of the ball
         * 
         * @param newSpeed New speed in units per second
         */
        void setSpeed(float newSpeed);

        /** Rest the ball position and velocity */
        void reset();

    private:
        /** Inital ball speed */
        float mInitalBallSpeed_ = 2.f;
        /** Radius of ball */
        float mRadius_ = 1.f;
    };
} // namespace pong