#include "SunEntity.h"
#include "App.h"

namespace galaxy {

SunEntity::SunEntity(Scene& scene)
    : Entity(scene) {
    mpRenderable_ = new ModelRenderable(
        mScene_.getResources().getResource<Model>("Sphere"),
        mScene_.getApp().getResources().getResource<Shader>("Assimp")
    );
    mpRenderable_->setScale({mRadius_, mRadius_, mRadius_});
    mpRenderable_->setColor(0xFFFF00FF);
    addRenderable(mpRenderable_);
    setPosition({0.f, 0.f, 0.f});
}

SunEntity::~SunEntity() {}

float SunEntity::getRadius() const {
    return mRadius_;
}

void SunEntity::setRadius(float radius) {
    mRadius_ = radius;
    mpRenderable_->setScale({mRadius_, mRadius_, mRadius_});
}

glm::vec4 SunEntity::getColor() const {
    return mpRenderable_->getColor();
}

void SunEntity::setColor(const glm::vec4& color) {
    mpRenderable_->setColor(color);
}

} // namespace galaxy