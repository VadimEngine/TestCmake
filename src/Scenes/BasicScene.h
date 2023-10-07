#pragma once
#include "Scene.h"
#include "Shader.h"
#include "Camera.h"
#include "CameraController.h"
#include "Texture.h"
#include "ShadedObject.h"
#include "BasicSceneGUI.h"

class BasicScene : public Scene {
public:
    unsigned int texId;

    CameraController cameraController;

    Shader* mpShader_;

    ShadedObject* mShadedObject = nullptr;

    BasicSceneGUI mGui_;


    BasicScene(App* theApp);

    void update(const float dt) override;

    void render(Renderer& renderer) override;

};