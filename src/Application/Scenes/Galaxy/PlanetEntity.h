#pragma once
#include "Entity.h"
#include "ModelRenderable.h"

namespace galaxy {

class PlanetEntity : public Entity {
private:
    float mRadius_ = 0.5f;
    float mOrbitRadius_ = 5.f;
    float mRotationSpeed_ = 1.f;

    ModelRenderable* mpRenderable_ = nullptr;

    // Scene pointer. Get loaded resources and use those for mesh/textures
    // also use scene pointer to get the other celestial bodies

public:
    PlanetEntity(Scene& scene);
    ~PlanetEntity();

    float getRadius() const;

    void setRadius(float radius);

    glm::vec4 getColor() const;

    void setColor(glm::vec4 color);

    float getRotationSpeed() const;

    void setRotationSpeed(float rotation);
};

} // namespace galaxy