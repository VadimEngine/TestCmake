#include "SunEntity.h"

namespace galaxy {

SunEntity::SunEntity(Scene& scene) 
    : Entity(scene) {
    mSphereModel_.loadMesh("./res/Sphere.obj");
    mpSunRenderable_ = new ModelRenderable(&mSphereModel_, Shader::getLoadedShader("Assimp"));
    mpSunRenderable_->setScale({mRadius_, mRadius_, mRadius_});
    mpSunRenderable_->setColor(0xFFFF00FF);
    addRenderable(mpSunRenderable_);
    setPosition({0.f, 0.f, 0.f});
}

SunEntity::~SunEntity() {
}

float SunEntity::getRadius() const {
    return mRadius_;
}

void SunEntity::setRadius(float radius) {
    mRadius_ = radius;
    mpSunRenderable_->setScale({mRadius_, mRadius_, mRadius_});
}

glm::vec4 SunEntity::getColor() const {
    return mpSunRenderable_->getColor();
}

void SunEntity::setColor(glm::vec4 color) {
    mpSunRenderable_->setColor(color);
}

} // namespace galaxy