#pragma once
#include "Scene.h"
#include "Shader.h"
#include "Camera.h"
#include "CameraController.h"
#include "Texture.h"
#include "ShadedObject.h"

class App;

class BasicScene : public Scene {
public:
    unsigned int texId;

    Camera mCamera_;

    CameraController cameraController;

    Shader* mpShader_;

    ShadedObject* mShadedObject = nullptr;
    ShadedObject* mShadedObject2 = nullptr;


    BasicScene(App* theApp);

    void update(const float dt) override;
    
    void render() override;
};