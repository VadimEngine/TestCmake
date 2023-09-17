#pragma once
#include "Scene.h"
#include "Shader.h"
#include "Camera.h"
#include "CameraController.h"

class App;

class BasicScene : public Scene {
public:

    float vertices[9] = {
        -0.5f, -0.5f, -5.0f,
        0.5f, -0.5f, -5.0f,
        0.0f,  0.5f, -5.0f
    }; 

    Camera mCamera_;

    CameraController cameraController;

    Shader* mpShader_;
    
    unsigned int VBO, VAO;

    BasicScene(App* theApp);

    void update(const float dt) override;
    
    void render() override;
};