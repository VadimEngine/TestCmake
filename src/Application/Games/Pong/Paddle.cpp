#include "Paddle.h"

namespace Pong {
    Paddle::Paddle(float xPos, float maxY, float minY) {
        mRectModel_.addMesh(*(Mesh::getLoadedMesh("RectPlane")));
        mXPosition_ = xPos;
        addRenderable(new ModelRenderable(&mRectModel_, Shader::getLoadedShader("Assimp")));
        addPhysicsComponent<RigidBodyComponent>();
        setPosition({xPos, 0.f, 0.f});
        setScale({.25f, .5, 1});
        RigidBodyComponent* rigid1 = getPhysicsComponent<RigidBodyComponent>();
        rigid1->getCollider().setShape(Collider::Shape::RECTANGLE);
    }

    Paddle::~Paddle() {}

    void Paddle::update(float dt) {
        Entity::update(dt);
        // keep paddle in bound
        if (mPosition_.y > mMaxHeight_ - 1.5f) {
            mPosition_.y = mMaxHeight_ - 1.5f;
        } else if (mPosition_.y < mMinHeight_ + 1.5f) {
            mPosition_.y = mMinHeight_ + 1.5f;
        }
    }

    void Paddle::reset() {
        setPosition({mXPosition_, 0.f, 0.f});
    }

    void Paddle::moveUp(float dt) {
        mPosition_.y += mMovementSpeed_ * dt;
    }

    void Paddle::moveDown(float dt) {
        mPosition_.y -= mMovementSpeed_ * dt;
    }

} // namespace Pong