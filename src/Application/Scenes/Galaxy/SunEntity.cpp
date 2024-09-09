// forward declare
#include "App.h"
// class
#include "SunEntity.h"

namespace galaxy {

SunEntity::SunEntity(Scene& scene)
    : Entity(scene), mLight_(LightSource::Type::Point) {
    mpRenderable_ = new ModelRenderable(
        mScene_.getResources().getResource<Model>("Sphere"),
        mScene_.getApp().getResources().getResource<Shader>("Assimp")
    );
    mpRenderable_->setScale({mRadius_, mRadius_, mRadius_});
    mpRenderable_->setColor({10,9,0,1});
    mLight_.setColor({1.2f, 1.2f, 0.0f, 1.0f});
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
    mLight_.setColor(color);
}

LightSource* SunEntity::getLightSource() {
    return &mLight_;
}

} // namespace galaxy