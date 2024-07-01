#include "Ball.h"
#include "Scene.h"
#include "App.h"

namespace pong {
    Ball::Ball(Scene& scene)
    : Entity(scene) {
        mCircleModel_.addSharedMesh(mScene_.getApp().getResources().getResource<Mesh>("CircularPlane"));

        addRenderable(new ModelRenderable(&mCircleModel_, mScene_.getApp().getResources().getResource<Shader>("Assimp")));
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
        // TODO check before normalize
        setVelocity(glm::normalize(dir) * mInitalBallSpeed_);
    }

    float Ball::getSpeed() {
        return glm::length(mVelocity_);
    }

    void Ball::setSpeed(float newSpeed) {
        // TODO check before normalize
        setVelocity(glm::normalize(mVelocity_) * newSpeed);
    }

    void Ball::reset() {
        setPosition({0,0,0});
        setVelocity({0,0,0});
    }

} // namespace pong