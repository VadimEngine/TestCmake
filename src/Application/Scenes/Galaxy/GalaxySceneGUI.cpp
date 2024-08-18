// forward declare
#include "App.h"
#include "GalaxyScene.h"
// class
#include "GalaxySceneGUI.h"

namespace galaxy {

GalaxySceneGUI::GalaxySceneGUI(GalaxyScene& theScene)
: mScene_(theScene) {
    mCameraMode_ = static_cast<int>(mScene_.getFocusCamera()->getMode());
}

GalaxySceneGUI::~GalaxySceneGUI() {}

void GalaxySceneGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Galaxy");
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 0.40f));
    if (ImGui::Button("Back")) {
        mScene_.getApp().setScene(new menu_scene::MenuScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    ImGui::PopStyleColor();
    ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));
    mSceneRunning_ = mScene_.isRunning();
    if (ImGui::Checkbox("Running", &mSceneRunning_)) {
        mScene_.setRunning(mSceneRunning_);
    }
    ImGui::Separator();
    buildCameraSection();
    ImGui::Separator();
    ImGui::Text("Sun");
    SunEntity* sunEntity = mScene_.getSunEntity();
    glm::vec3 sunPosition = sunEntity->getPosition();
    float sunRadius = sunEntity->getRadius();
    glm::vec4 sunColor = sunEntity->getColor();

    ImGui::Text("Position: %.2f %.2f %.2f", sunPosition.x, sunPosition.y, sunPosition.z);
    // position
    if (ImGui::SliderFloat3("Position##Sun", glm::value_ptr(sunPosition), -10.f, 10.f, "%.2f")) {
        sunEntity->setPosition(sunPosition);
    }
    // radius
    if (ImGui::SliderFloat("Radius##Sun", &sunRadius, 0, 100.f)) {
        sunEntity->setRadius(sunRadius);
    }
    // brightness
    // color
    if (ImGui::ColorEdit4("Color##Sun", glm::value_ptr(sunColor))) {
        sunEntity->setColor(sunColor);
    }

    ImGui::Separator();
    ImGui::Text("Planet");
    PlanetEntity* planetEntity = mScene_.getPlanetEntity();
    glm::vec3 planetPosition = planetEntity->getPosition();
    float planetRadius = planetEntity->getRadius();
    float planetRotationSpeed = planetEntity->getRotationSpeed();
    glm::vec4 planetColor = planetEntity->getColor();

    // position
    ImGui::Text("Position: %.2f %.2f %.2f", planetPosition.x, planetPosition.y, planetPosition.z);
    // radius
    if (ImGui::SliderFloat("Radius##Planet", &planetRadius, 0, 100.f)) {
        planetEntity->setRadius(planetRadius);
    }
    // rotation speed
    if (ImGui::SliderFloat("Rotation Speed##Planet", &planetRotationSpeed, 0, 100.f)) {
        planetEntity->setRotationSpeed(planetRotationSpeed);
    }
    // color
    if (ImGui::ColorEdit4("Color##Planet", glm::value_ptr(planetColor))) {
        planetEntity->setColor(glm::make_vec4(planetColor));
    }
    // pause
    // rot speed
    ImGui::Separator();
    ImGui::Text("Moon");
    MoonEntity* moonEntity = mScene_.getMoonEntity();
    glm::vec3 moonPos = moonEntity->getPosition();
    float moonRadius = moonEntity->getRadius();
    float moonRotationSpeed = moonEntity->getRotationSpeed();
    glm::vec4 moonColor = moonEntity->getColor();

    // position
    ImGui::Text("Position: %.2f %.2f %.2f", moonPos.x, moonPos.y, moonPos.z);
    // radius
    if (ImGui::SliderFloat("Radius##Moon", &moonRadius, 0, 100.f)) {
        moonEntity->setRadius(moonRadius);
    }
    // rotation speed
    if (ImGui::SliderFloat("Rotation Speed##Moon", &moonRotationSpeed, 0, 100.f)) {
        moonEntity->setRotationSpeed(moonRotationSpeed);
    }
    // color
    if (ImGui::ColorEdit4("Color##Moon", glm::value_ptr(moonColor))) {
        moonEntity->setColor(glm::make_vec4(moonColor));
    }
    // rot speed
    ImGui::End();
};

void GalaxySceneGUI::buildCameraSection() {
    ImGui::Text("Camera");
    ImGui::Text("Camera Mode");
    if (ImGui::RadioButton("Perspective", &mCameraMode_, 0)) {
        mScene_.getFocusCamera()->setMode(static_cast<Camera::CameraMode>(mCameraMode_));
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Orthogonal", &mCameraMode_, 1)) {
        mScene_.getFocusCamera()->setMode(static_cast<Camera::CameraMode>(mCameraMode_));
    }

    ImGui::Text("Camera Movement");
    glm::vec3 camPosition = mScene_.getFocusCamera()->getPosition();
    ImGui::Text(
        "Position: %.2f %.2f %.2f",
        camPosition.x,
        camPosition.y,
        camPosition.z
    );
    glm::vec3 camForward = mScene_.getFocusCamera()->getForward();
    ImGui::Text(
        "Direction: %.2f %.2f %.2f",
        camForward.x,
        camForward.y,
        camForward.z
    );
    ImGui::Text(
        "FOV: %.2f",
        mScene_.getFocusCamera()->getFOV()
    );
}

} // namespace galaxy