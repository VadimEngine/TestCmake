#pragma once
#include "SpriteSheet.h"
#include "Renderer.h"
#include "Camera.h"
#include "BaseRenderable.h"
#include "SpriteRenderable.h"
#include "Collider2.h"
#include "Entity.h"

namespace RPG2D {

    class MOB : public Entity {
    private:
        float speed = 5.0f;
    public:
        SpriteSheet mSpriteSheet_;
        // TODO try Collider2.h

        Collider2* mpCollider_ = nullptr;

        BoxCollider2D* mpBoxCollider_ = nullptr;


        MOB();

        ~MOB();

        void update(float dt) override;

        void move(glm::vec3 direction, float dt);

        Collider2& getCollider();

        Collider& getColliderNew();
    };

} // namespace RPG2D