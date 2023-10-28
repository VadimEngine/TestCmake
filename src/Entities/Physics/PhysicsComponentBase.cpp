#include "PhysicsComponentBase.h"

void PhysicsComponentBase::setEnabled(const bool isEnabled) {
    mEnabled_ = isEnabled;
}

bool PhysicsComponentBase::isEnabled() const {
    return mEnabled_;
}