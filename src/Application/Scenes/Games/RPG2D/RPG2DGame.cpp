// forward declare
#include "App.h"
#include "RPG2DScene.h"
// class
#include "RPG2DGame.h"
// temp include
#include <iostream>

namespace rpg_2d {

    RPG2DGame::RPG2DGame(RPG2DScene& scene, Camera& focusCamera)
    : mScene_(scene), mApp_(mScene_.getApp()), thePlayer(mScene_), theMOB(mScene_),
     mCameraController_(&focusCamera, mApp_.getWindow().getInputHandler()),
     mInputHandler_(mApp_.getWindow().getInputHandler()) {}

    RPG2DGame::~RPG2DGame() {}


    void RPG2DGame::update(const float dt) {
        handleKeyUpdate(dt);

        //if (thePlayer.getCollider().getCollisionNormal(&(theMOB.getCollider()))) {
        //    thePlayer.getCollider().onCollisionEnter(theMOB.getCollider());
        //}

        if (thePlayer.getColliderNew().isColliding(theMOB.getColliderNew())) {
            thePlayer.getColliderNew().onCollisionEnter(theMOB.getColliderNew());
        } else {
            // std::cout << "No collide" << std::endl;
        }

        thePlayer.update(dt);
        theMOB.update(dt);
    }

    void RPG2DGame::render(Renderer& theRenderer, Camera& theCamera) {
        thePlayer.render(theRenderer, theCamera);

        theMOB.render(theRenderer, theCamera);
        theMOB.getCollider().render(theRenderer, theCamera);
        // draw player collider for debugging
        theRenderer.renderText(
            "RPG",
            {350.0f, 500.0f},
            *(mApp_.getResources().getResource<Font>("Consolas")),
            1.0f,
            {1.f, 1.f, 1.f}
        );
    }

    void RPG2DGame::handleKeyUpdate(float dt) {
        glm::vec3 dir = {0,0,0};
        if (mInputHandler_.isKeyPressed(GLFW_KEY_W)) {
            dir.y += 1;
        }
        if (mInputHandler_.isKeyPressed(GLFW_KEY_D)) {
            dir.x += 1;
        }
        if (mInputHandler_.isKeyPressed(GLFW_KEY_S)) {
            dir.y -= 1;
        }
        if (mInputHandler_.isKeyPressed(GLFW_KEY_A)) {
            dir.x -= 1;
        }
        thePlayer.move(dir, dt);
    }

    void RPG2DGame::onKeyPress(unsigned int keyCode) {
        if (!ImGuiComponent::keyboardGUIFocus()) { }
    }

    void RPG2DGame::onKeyRelease(unsigned int keyCode) {}

    void RPG2DGame::onMousePress(const InputHandler::MouseEvent& mouseEvent) {
        // TODO check if mouse collides with player's collider2
        glm::ivec2 mousePosition = mouseEvent.getPosition();
        glm::ivec2 screenSize = mApp_.getWindow().getWindowDimensions(); // get this incase the size changes

        mApp_.getWindow().getWindowDimensions();
        glm::vec3 ray_ndc(
            (2.0f * mousePosition.x) / screenSize.x - 1.0f,
            1.0f - (2.0f * mousePosition.y) / screenSize.y,
            1.0f
        );

        glm::vec4 ray_clip(ray_ndc.x, ray_ndc.y, -1.0, 1.0);
        glm::mat4 inverseProjectionMatrix = glm::inverse(mCameraController_.getCamera()->getProjectionMatrix());
        glm::vec4 ray_eye = inverseProjectionMatrix * ray_clip;
        ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);

        glm::mat4 inverseViewMatrix = glm::inverse(mCameraController_.getCamera()->getViewMatrix());
        glm::vec4 ray_world = inverseViewMatrix * ray_eye;
        glm::vec3 ray_direction = glm::normalize(glm::vec3(ray_world));

        glm::vec3 cameraPos = mCameraController_.getCamera()->getPosition();

        if (thePlayer.getCollider().rayCollides(cameraPos, ray_direction)) {
            std::cout << "Player collide" << std::endl;
        } else {
            std::cout << "Player not collide" << std::endl;
        }
    }

} // namespace rpg_2d