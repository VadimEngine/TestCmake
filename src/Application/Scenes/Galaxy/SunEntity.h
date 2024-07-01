#pragma once
#include "Entity.h"
#include "ModelRenderable.h"

namespace galaxy {

class SunEntity : public Entity {
private:
    float mRadius_ = 1;
    ModelRenderable* mpRenderable_ = nullptr;

public:
    SunEntity(Scene& scene);

    ~SunEntity();

    float getRadius() const;

    void setRadius(float radius);

    glm::vec4 getColor() const;

    void setColor(glm::vec4 color);
};

} // namespace galaxy