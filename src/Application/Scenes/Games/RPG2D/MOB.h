#pragma once
// project
#include "BaseRenderable.h"
#include "Collider2.h"
#include "Entity.h"
#include "Renderer.h"
#include "SpriteRenderable.h"
#include "SpriteSheet.h"

namespace rpg_2d {
    class MOB : public Entity {
    public:
        // TODO try Collider2.h
        Collider2* mpCollider_ = nullptr;

        BoxCollider2D* mpBoxCollider_ = nullptr;

        SpriteSheet::Sprite mSprite_;


        MOB(Scene& scene);

        ~MOB();

        void update(float dt) override;

        void move(glm::vec3 direction, float dt);

        Collider2& getCollider();

        Collider& getColliderNew();

    private:
        float speed = 5.0f;
    };

} // namespace rpg_2d