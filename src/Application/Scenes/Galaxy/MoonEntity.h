#pragma once
#include "Entity.h"
#include "ModelRenderable.h"

namespace galaxy {

class GalaxyScene;

class MoonEntity : public Entity {
private:
    float mRadius_ = 0.25f;
    float mOrbitRadius_ = 1.f;
    float mRotationSpeed_ = 12.f;
    ModelRenderable* mpRenderable_ = nullptr;


public:
    MoonEntity(GalaxyScene& mScene);
    ~MoonEntity();

    float getRadius() const;

    void setRadius(float radius);

    glm::vec4 getColor() const;

    void setColor(glm::vec4 color);

    float getRotationSpeed() const;

    void setRotationSpeed(float rotation);
};

} // namespace galaxy