#include "CameraController.h"
#include "Camera.h"


CameraController::CameraController(Camera* pCamera, InputHandler* pInputHandler)
    :mpCamera_(pCamera), mpInputHandler_(pInputHandler) {}

void CameraController::update(float dt) {
    if (mpInputHandler_->isKeyPressed(GLFW_KEY_Q)) {
        mpCamera_->rotate({0,0,1}, 20.0f * dt);
    }
    if (mpInputHandler_->isKeyPressed(GLFW_KEY_E)) {
        mpCamera_->rotate({0,0,1}, -20.0f * dt);
    }
    if (mpInputHandler_->isKeyPressed(GLFW_KEY_W)) {
        mpCamera_->move(mpCamera_->getForward(), .2f * dt);
    }
    if (mpInputHandler_->isKeyPressed(GLFW_KEY_S)) {
        mpCamera_->move(mpCamera_->getForward(), -.2f * dt);
    }
    if (mpInputHandler_->isKeyPressed(GLFW_KEY_A)) {
        mpCamera_->move(mpCamera_->getRight(), -.2f * dt);
    }
    if (mpInputHandler_->isKeyPressed(GLFW_KEY_D)) {
        mpCamera_->move(mpCamera_->getRight(), .2f * dt);
    }

    if (mpInputHandler_->isKeyPressed(GLFW_KEY_LEFT)) {
        mpCamera_->rotate({0,1,0}, 2.0f * dt);
    }
    if (mpInputHandler_->isKeyPressed(GLFW_KEY_RIGHT)) {
        mpCamera_->rotate({0,1,0}, -2.0f * dt);
    }
    if (mpInputHandler_->isKeyPressed(GLFW_KEY_UP)) {
        mpCamera_->rotate({1,0,0}, 2.0f * dt);
    }
    if (mpInputHandler_->isKeyPressed(GLFW_KEY_DOWN)) {
        mpCamera_->rotate({1,0,0}, -2.0f * dt);
    }

    if (mpInputHandler_->isKeyPressed(GLFW_KEY_PERIOD)) {
        mpCamera_->zoom(-2.0f * dt);
    }
    if (mpInputHandler_->isKeyPressed(GLFW_KEY_COMMA)) {
        mpCamera_->zoom(2.0f * dt);
    }
}
