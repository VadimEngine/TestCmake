// forward declare
#include "App.h"
// class
#include "GalaxyScene.h"

namespace galaxy {

GalaxyScene::GalaxyScene(App& theApp)
    : Scene(theApp), mGui_(*this), mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()) {
    getFocusCamera()->setPosition({0,2,10});
    assembleResources();
    // sun
    sunEntity_ = new SunEntity(*this);
    mEntities_.push_back(sunEntity_);
    // planet
    planetEntity_ = new PlanetEntity(*this);
    mEntities_.push_back(planetEntity_);
    // moon
    moonEntity_ = new MoonEntity(*this);
    mEntities_.push_back(moonEntity_);
    mApp_.getRenderer().enableGammaCorrect(true);
}

GalaxyScene::~GalaxyScene() {
    // Delete Entities
    for (auto eachEntity: mEntities_) {
        delete eachEntity;
    }
}

void GalaxyScene::update(const float dt) {
    mCameraController_.update(dt);
    // mouse wheel move zoom
    if (mIsRunning_) {
        glm::vec3 planetDiff;
        {
            glm::vec3 orbitCenter = sunEntity_->getPosition();

            // Update planet orbit
            glm::vec3 planetPos = planetEntity_->getPosition();

            // Calculate relative position of the planet with respect to the center of the orbit
            glm::vec3 relativePos = planetPos - orbitCenter;

            // Calculate angle of rotation based on current position
            float planetAngle = glm::atan(relativePos.z, relativePos.x);

            // Calculate distance from center
            float radius = glm::length(glm::vec2(relativePos.x, relativePos.z));

            // Update angle if planet is not at the center
            if (radius > 0.0f) {
                // Adjust the speed of rotation as needed
                planetAngle += planetEntity_->getRotationSpeed() * dt;
            }

            // Calculate new position of the planet
            float x = orbitCenter.x + radius * glm::cos(planetAngle);
            float z = orbitCenter.z + radius * glm::sin(planetAngle);
            glm::vec3 newPos = glm::vec3(x, orbitCenter.y, z); // Y-coordinate remains the same as orbit center

            planetDiff = newPos - planetPos;

            // Update planet position
            planetEntity_->setPosition(newPos);
        }
        {
            // move moon
            moonEntity_->setPosition(moonEntity_->getPosition() + planetDiff);

            // orbit moon around planet
            glm::vec3 orbitCenter = planetEntity_->getPosition();
            glm::vec3 moonPos = moonEntity_->getPosition();

            glm::vec3 relativePos = moonPos - orbitCenter;

            float moonAngle = glm::atan(relativePos.z, relativePos.x);
            float radius = glm::length(glm::vec2(relativePos.x, relativePos.z));

            // Update angle if moon is not at the center
            if (radius > 0.0f) {
                // Adjust the speed of rotation as needed
                moonAngle += moonEntity_->getRotationSpeed() * dt;
            }
            // Calculate new position of the planet
            float x = orbitCenter.x + radius * glm::cos(moonAngle);
            float z = orbitCenter.z + radius * glm::sin(moonAngle);
            glm::vec3 newPos = glm::vec3(x, orbitCenter.y, z); // Y-coordinate remains the same as orbit center

            // Update planet position
            moonEntity_->setPosition(newPos);
        }
    }
}

void GalaxyScene::render(Renderer& renderer) {
    renderer.setBloom(true);
    renderer.setLightSources({sunEntity_->getLightSource()});
    renderer.setCamera(getFocusCamera());
    for (int i = 0; i < mEntities_.size(); ++i) {
        mEntities_[i]->render(renderer);
    }
    renderer.setBloom(false);
}

void GalaxyScene::renderGUI() {
    mGui_.render();
}

SunEntity* GalaxyScene::getSunEntity() {
    return sunEntity_;
}

PlanetEntity* GalaxyScene::getPlanetEntity() {
    return planetEntity_;
}

MoonEntity* GalaxyScene::getMoonEntity() {
    return moonEntity_;
}

void GalaxyScene::assembleResources() {
    mResources_.loadResource<Model>(
        {Resource::RESOURCE_PATH / "Torus.obj"},
        "Torus"
    );
    std::unique_ptr<Model> sphereModel = std::make_unique<Model>();
    sphereModel->addSharedMesh(mApp_.getResources().getResource<Mesh>("Sphere"));
    mResources_.addResource(
        std::move(sphereModel),
        "Sphere"
    );
}

Resource& GalaxyScene::getResources() {
    return mResources_;
}

void GalaxyScene::onMouseWheel(const InputHandler::MouseEvent& mouseEvent) {
    // Calculate the movement amount based on the scroll amount and the scroll factor
    float movement = 2;
    if (mouseEvent.getType() == InputHandler::MouseEvent::Type::SCROLL_DOWN) {
        movement*= -1;
    }

    // Move the camera along its forward direction
    mCameraController_.getCamera()->move( mCameraController_.getCamera()->getForward(), movement);
}

} // namespace galaxy