#pragma once
#include <optional>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"

class Collider2 {
public:
    /** Possible shapes for a collider: TODO maybe class that has vertices */
    enum class Shape {CIRCLE, RECTANGLE};

    /** Description of the shape of this collider */
    Shape mShape_;

    
    /** Dimensions of this Collider */
    glm::vec3 mDimension_ = {1.f, 1.f, 1.f};

    glm::vec3 mPosition_ = {0,0,0};

    Collider2();

    ~Collider2();

    void render(const Renderer& theRenderer, const Camera& theCamera);

    std::optional<glm::vec3> getCollisionNormal(Collider2* otherCollider) const;

    bool rayCollides(glm::vec3 rayOrigin, glm::vec3 rayDirection) const;

    Shape getShape() const;

    void setShape(const Shape& theShape);

    void setPosition(const glm::vec3 newPosition);

    glm::vec3 getDimension() const;

    glm::vec3 getPosition();

    void setDimension(const glm::vec3& newDimension);

    // TODO onEnter/onCollide/onExit?


};