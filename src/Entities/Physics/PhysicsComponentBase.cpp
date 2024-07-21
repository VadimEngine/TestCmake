// forward declare
#include "Entity.h"
// class
#include "PhysicsComponentBase.h"

PhysicsComponentBase::PhysicsComponentBase(Entity& parentEntity)
    : mParentEntity_(parentEntity) {}


void PhysicsComponentBase::setEnabled(const bool isEnabled) {
    mEnabled_ = isEnabled;
}

bool PhysicsComponentBase::isEnabled() const {
    return mEnabled_;
}

Entity& PhysicsComponentBase::getEntity() {
    return mParentEntity_;
}
