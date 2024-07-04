#include "MOB.h"
#include "Scene.h"
#include "App.h"

namespace rpg_2d {
    MOB::MOB(Scene& scene)
    : Entity(scene), mSprite_(*mScene_.getApp().getResources().getResource<SpriteSheet>("SpriteSheet1"), {0,0}) {
        // TODO use sprite sheet to add sprite
        addRenderable(new SpriteRenderable(&mSprite_));
        mpCollider_ = addPhysicsComponent<Collider2>();
        mpCollider_->setShape(Collider2::Shape::RECTANGLE);
        // mpCollider_->addOnCollisionEnterCallback(separateFromMOB);
        // collider shape is 1x1x1
        mpBoxCollider_ = addPhysicsComponent<BoxCollider2D>();
    }

    MOB::~MOB() {}

    void MOB::update(float dt) {
        Entity::update(dt);
        mpCollider_->setPosition(mPosition_);
    }

    void MOB::move(glm::vec3 direction, float dt) {
        setPosition(getPosition() + direction * speed * dt);
    }

    Collider2& MOB::getCollider() {
        return *mpCollider_;
    }

    Collider& MOB::getColliderNew() {
        return *mpBoxCollider_;
    }

} // namespace rpg_2d