#pragma once
#include "InputHandler.h"
#include <GLFW/glfw3.h>

// forward declare Camera
class Camera;

class CameraController {
private:
    /** Camera being controlled */
    Camera* mpCamera_ = nullptr;
    /** Input handler to get input from */
    InputHandler& mInputHandler_;
public:
    /**
     * Constructor.
     * \param pCamera Camera to be controlled
     * \param pInputHandler Input handler to listen to
     */
    CameraController(Camera* pCamera, InputHandler& theInputHandler);

    /**
     * Update the camera based on inputs 
     * \param dt Time since last update (in seconds)
     */
    void update(float dt);

    /** Set the camera to be controlled */
    void setCamera(Camera* newCamera);
};