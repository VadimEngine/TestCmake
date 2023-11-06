#include "RigidBodyComponent.h"
#include "Entity.h"

RigidBodyComponent::RigidBodyComponent(Entity& theEntity)
    : mEntity_(theEntity), mCollider_(*this){}

RigidBodyComponent::~RigidBodyComponent() {}

void RigidBodyComponent::update(float dt) {
    if (mMobile_) {
        /// gravity down
        glm::vec3 currVel = mEntity_.getVelocity();
        currVel.y += -9.81f * mGravityScale_ * dt;

        mEntity_.setVelocity(currVel);
    }
}

PhysicsComponentBase::ComponentType RigidBodyComponent::getType() const {
    return PhysicsComponentBase::ComponentType::RIGID_BODY;
}

Entity& RigidBodyComponent::getEntity() {
    return mEntity_;
}

Collider& RigidBodyComponent::getCollider() {
    return mCollider_;
}

bool RigidBodyComponent::handleIfCollision(RigidBodyComponent* other) {
    std::optional<glm::vec3> thisCollisionNormal = mCollider_.getCollisionNormal(&(other->getCollider()));

    if (thisCollisionNormal.has_value()) {
        bool collision = false;
        Entity& thisEntity = mEntity_;
        Entity& otherEntity = other->getEntity();

        if (this->mMobile_) {
            thisEntity.setVelocity(
                glm::reflect(thisEntity.getVelocity(), glm::normalize( thisCollisionNormal.value()))
            );
            collision = true;
        }

        if (other->mMobile_) {
            otherEntity.setVelocity(
                glm::reflect(otherEntity.getVelocity(), glm::normalize( -thisCollisionNormal.value()))
            );
            collision = true;
        }
        return collision;
    } else {
        return false;
    }
}

void RigidBodyComponent::applyIfAttraction(RigidBodyComponent* other, float dt) {
    if (mAttractive_ && other->mAttractive_) {
        float distance = glm::length(mEntity_.getPosition() - other->mEntity_.getPosition());

        if (distance != 0) {
            float scale = 5;

            glm::vec3 dir = glm::vec3(
                mEntity_.getPosition().x - other->mEntity_.getPosition().x,
                mEntity_.getPosition().y - other->mEntity_.getPosition().y,
                0.0f
            );

            glm::vec3 newVeli = (mEntity_.getVelocity() - (dir * (scale * (1.0f / pow(distance, 2.0f)) * dt)));
            glm::vec3 newVelj = (other->mEntity_.getVelocity() + (dir * (scale * (1.0f / pow(distance, 2.0f)) * dt)));

            if (mMobile_) {
                mEntity_.setVelocity(newVeli);
            }

            if (other->mMobile_) {
                other->mEntity_.setVelocity(newVelj);
            }
        }
    }
}

float RigidBodyComponent::getMass() {
    return mMass_;
}

float RigidBodyComponent::getGravityScale() {
    return mGravityScale_;
}

bool RigidBodyComponent::isMobile() {
    return mMobile_;
}

bool RigidBodyComponent::isAttractive() {
    return mAttractive_;
}

void RigidBodyComponent::setMass(float newMass) {
    mMass_ = newMass;
}

void RigidBodyComponent::setGravityScale(float newGravity) {
    mGravityScale_ = newGravity;
}

void RigidBodyComponent::setMobile(bool newMobile) {
    mMobile_ = newMobile;
}

void RigidBodyComponent::setAttractive(bool newAttractive) {
    mAttractive_ = newAttractive;
}