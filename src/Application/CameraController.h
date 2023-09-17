#pragma once
#include "InputHandler.h"
#include <GLFW/glfw3.h>

// forward declare Camera
class Camera;

class CameraController {
private:
    Camera* mpCamera_ = nullptr;
    InputHandler* mpInputHandler_ = nullptr;
public:

    CameraController(Camera* camera, InputHandler* pInputHandler);

    void update(float dt);
};