#pragma once
#include "Collider.h"

class Entity;

class BoxCollider2D : public Collider {
public: 
    BoxCollider2D(Entity& parentEntity);

    bool isColliding(const Collider& other) const override;

    void update(float dt);
    
    void render(const Renderer& theRenderer, const Camera& theCamera);

    std::optional<glm::vec3> getCollisionMTV(const Collider& other) const;

};