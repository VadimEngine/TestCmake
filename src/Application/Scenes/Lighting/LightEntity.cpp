// forward declare
#include "App.h"
// class
#include "LightEntity.h"

namespace lighting_scene {
    LightEntity::LightEntity(Scene& scene)
    : Entity(scene), mLightSource_(LightSource::Type::Point) {
        mpRenderable_ = new ModelRenderable(
            mScene_.getResources().getResource<Model>("Sphere"),
            mScene_.getApp().getResources().getResource<Shader>("Assimp")
        );
        addRenderable(mpRenderable_);
    }

    void LightEntity::setPosition(const glm::vec3& newPosition) {
        Entity::setPosition(newPosition);
        mLightSource_.setPosition(newPosition);
    }

    void LightEntity::setColor(glm::vec4 newColor) {
        mpRenderable_->setColor(newColor);
        mLightSource_.setColor(newColor);
    }


    LightSource* LightEntity::getLightSource() {
        return &mLightSource_;
    }

    glm::vec4 LightEntity::getColor() const {
        return mLightSource_.getColor();
    }

}// namespace lighting_scene