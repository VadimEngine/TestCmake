// forward declare
#include "VesselsGame.h"
#include "VesselsScene.h"
// class
#include "Player.h"

namespace vessels {

    Player::Player(VesselsGame& theGame)
    : Entity(theGame.getScene()) {}

    void Player::update(const float dt) {
    }

    void Player::render(const Renderer& theRenderer) const {
        Entity::render(theRenderer);
    }

    void Player::renderInMenu(const Renderer& theRenderer, const glm::vec2& guiPosition, const glm::vec3& scale, const glm::vec3& rotation) {
        
    }

    glm::vec3 Player::getForward() {
        // Start with a default forward vector (looking down the negative Z-axis)
        glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);

        // Create the rotation matrix and apply rotations for yaw (Y-axis), pitch (X-axis), and roll (Z-axis)
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(mRotation_.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll

        forward = glm::vec3(rotationMatrix * glm::vec4(forward, 1.0f));

        // Normalize the result to ensure the vector has length 1
        return glm::normalize(forward);
    }

    glm::vec3 Player::getRight() {
        // Start with a default Right vector (looking down the X-axis)
        glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

        // Create the rotation matrix and apply rotations for yaw (Y-axis), pitch (X-axis), and roll (Z-axis)
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(mRotation_.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(mRotation_.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll

        right = glm::vec3(rotationMatrix * glm::vec4(right, 1.0f));

        // Normalize the result to ensure the vector has length 1
        return glm::normalize(right);
    }



} // namespace vessels