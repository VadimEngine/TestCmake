#include "Collider.h"
#include "Entity.h"

Collider::Collider(Entity& parentEntity)
    : PhysicsComponentBase(parentEntity) {
}

PhysicsComponentBase::ComponentType Collider::getType() const {
    return PhysicsComponentBase::ComponentType::COLLIDER;
}

void Collider::addOnCollisionEnterCallback(const OnCollisionCB& cb) {
}

void Collider::addOnCollisionExitCallback(const OnCollisionCB& cb) {}

void Collider::onCollisionEnter(Collider& other) {}

void Collider::onCollisionExit(Collider& other){}

glm::vec3 Collider::getPosition() const {
    return mPosition_;
}

glm::vec3 Collider::getScale() const {
    return mScale_;
}