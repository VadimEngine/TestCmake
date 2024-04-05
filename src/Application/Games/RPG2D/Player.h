#pragma once
#include "SpriteSheet.h"
#include "Renderer.h"
#include "Camera.h"
#include "BaseRenderable.h"
#include "SpriteRenderable.h"
#include "Collider2.h"
#include "Entity.h"

namespace RPG2D {

    class Player : public Entity { // TODO extend Entity
    private:
        float speed = 5.0f;
    public:
        SpriteSheet mSpriteSheet_;
        // TODO try Collider2.h

        Collider2* mpCollider_ = nullptr;

        BoxCollider2D* mpBoxCollider_ = nullptr;

        Player();

        ~Player();

        void update(float dt) override;

        void render(const Renderer& theRenderer, const Camera& theCamera) const override;

        void move(glm::vec3 direction, float dt);

        Collider2& getCollider();

        Collider& getColliderNew();


        void separateFromMOB2(Collider2& thisCollider, Collider2& otherCollider);

        void separateFromMOB(Collider& thisCollider, Collider& otherCollider);

    };

} // namespace RPG2D