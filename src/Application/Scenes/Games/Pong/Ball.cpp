#include "Ball.h"
#include "Scene.h"
#include "App.h"

namespace pong {
    Ball::Ball(Scene& scene)
    : Entity(scene) {
        addRenderable(new ModelRenderable(
            mScene_.getResources().getResource<Model>("CircularPlane"),
            mScene_.getApp().getResources().getResource<Shader>("Assimp")
        ));
        mPosition_ = {0.f,0.f,0.f};
        mScale_ = {.25, .25, 1};
        RigidBodyComponent* rigid3 = addPhysicsComponent<RigidBodyComponent>();
        rigid3->getCollider().setShape(ColliderOLD::Shape::CIRCLE);
    }

    Ball::~Ball() {}

    void Ball::update(float dt) {
        Entity::update(dt);
        // Bounce off top/bottom
        if (mPosition_.y < (-5.f +1.f) || mPosition_.y > (5.f - 1.f)) {
            glm::vec3 ballVel = getVelocity();
            ballVel.y *= -1;
            setVelocity(ballVel);
        }
    }

    void Ball::start(const glm::vec3& dir) {
        const float epsilon = 1e-6f;
        if (glm::length2(dir) > epsilon) {
            setVelocity(glm::normalize(dir) * mInitalBallSpeed_);
        } else {
            // if dir is zero, then set velocity to zero
            setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
        }
    }

    float Ball::getSpeed() {
        return glm::length(mVelocity_);
    }

    void Ball::setSpeed(float newSpeed) {
        const float epsilon = 1e-6f;
        setVelocity(glm::normalize(mVelocity_) * newSpeed);
        if (glm::length2(mVelocity_) > epsilon) {
            setVelocity(glm::normalize(mVelocity_) * newSpeed);
        } else {
            // if velocity is zero, then set velocity to zero
            setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
        }
    }

    void Ball::reset() {
        setPosition({0,0,0});
        setVelocity({0,0,0});
    }

} // namespace pong