#include "Player.h"
#include "Scene.h"
#include "App.h"

namespace rpg_2d {

    Player::Player(Scene& scene)
    : Entity(scene), mSpriteSheet_(mScene_.getApp().getResources().getResource<Texture>("SpriteSheet")->getId(), {512, 512}, {16,16}) {
        // TODO use sprite sheet to add sprite
        addRenderable(new SpriteRenderable(new SpriteSheet::Sprite(&mSpriteSheet_, glm::ivec2(3, 0))));
        mpCollider_ = addPhysicsComponent<Collider2>();
        mpCollider_->setShape(Collider2::Shape::RECTANGLE);
        mpCollider_->addOnCollisionEnterCallback(std::bind(&Player::separateFromMOB2, this, std::placeholders::_1, std::placeholders::_2));
        // collider shape is 1x1x1
        mpBoxCollider_ = addPhysicsComponent<BoxCollider2D>();

        mpBoxCollider_->addOnCollisionEnterCallback(std::bind(&Player::separateFromMOB, this, std::placeholders::_1, std::placeholders::_2));
    }

    Player::~Player() {}

    void Player::update(float dt) {
        Entity::update(dt);
        mpCollider_->setPosition(mPosition_);

        // TODO have collider's position match the parent Entity
    }

    void Player::render(const Renderer& theRenderer, const Camera& theCamera) const {
        Entity::render(theRenderer, theCamera);
        // mpCollider_->render(theRenderer, theCamera);
        mpBoxCollider_->render(theRenderer, theCamera);
    }

    void Player::move(glm::vec3 direction, float dt) {
        setPosition(getPosition() + direction * speed * dt);
    }

    Collider2& Player::getCollider() {
        return *mpCollider_;
    }

    Collider& Player::getColliderNew() {
        return *mpBoxCollider_;
    }

    void Player::separateFromMOB2(Collider2& thisCollider, Collider2& otherCollider) {
        LOG_I("Player Collide2");

        // get MTV and separate
        auto theMVT = thisCollider.getCollisionMVT(&otherCollider);

        LOG_I("MTV %.2f, %.2f, %.2f", theMVT.value().x, theMVT.value().y, theMVT.value().z);

        setPosition(getPosition() + theMVT.value());
        otherCollider.getEntity().setPosition(otherCollider.getEntity().getPosition() - theMVT.value());
    }

    void Player::separateFromMOB(Collider& thisCollider, Collider& otherCollider) {
        LOG_I("Player Collide");

        auto mvt = thisCollider.getCollisionMTV(otherCollider);

        if (mvt.has_value()) {
            mPosition_ += mvt.value();
        }

        // get MTV and separate
        //auto theMVT = thisCollider.getCollisionMVT(&otherCollider);

        //LOG_I("MTV %.2f, %.2f, %.2f", theMVT.value().x, theMVT.value().y, theMVT.value().z);

        //setPosition(getPosition() + theMVT.value());
        //otherCollider.getEntity().setPosition(otherCollider.getEntity().getPosition() - theMVT.value());
    }

} // namespace rpg_2d