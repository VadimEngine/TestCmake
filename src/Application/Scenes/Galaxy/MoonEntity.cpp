#include "MoonEntity.h"
#include "App.h"

namespace galaxy {
    MoonEntity::MoonEntity(Scene& scene)
        : Entity(scene) {
        mpRenderable_ = new ModelRenderable(
            mScene_.getResources().getResource<Model>("Sphere"),
            mScene_.getApp().getResources().getResource<Shader>("Assimp")
        );
        mpRenderable_->setScale({mRadius_, mRadius_, mRadius_});
        mpRenderable_->setColor(0x9A9A9AFF);
        // Add Sphere to Entity
        addRenderable(mpRenderable_);
        // TODO use orbit center position as reference
        setPosition({5 + mOrbitRadius_, 0.f, 0.f});
    }

    MoonEntity::~MoonEntity() {}

    float MoonEntity::getRadius() const {
        return mRadius_;
    }

    void MoonEntity::setRadius(float radius) {
        mRadius_ = radius;
        mpRenderable_->setScale({mRadius_, mRadius_, mRadius_});
    }

    glm::vec4 MoonEntity::getColor() const {
        return mpRenderable_->getColor();
    }

    void MoonEntity::setColor(const glm::vec4& color) {
        mpRenderable_->setColor(color);
    }

    float MoonEntity::getRotationSpeed() const {
        return mRotationSpeed_;
    }

    void MoonEntity::setRotationSpeed(float rotation) {
        mRotationSpeed_ = rotation;
    }
} // namespace galaxy