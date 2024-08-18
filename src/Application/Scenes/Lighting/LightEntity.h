#pragma once
// project
#include "Entity.h"
#include "LightSource.h"
#include "ModelRenderable.h"

namespace lighting_scene {
    class LightEntity : public Entity {
    public:
        LightEntity(Scene& scene);

        LightSource* getLightSource();

        void setPosition(const glm::vec3& newPosition) override;

        void setColor(glm::vec4 newColor);

        glm::vec4 getColor() const;

    private:
        ModelRenderable* mpRenderable_ = nullptr;
        LightSource mLightSource_;
    };

} // namespace lighting_scene