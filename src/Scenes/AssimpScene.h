#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Scene.h"
#include "Camera.h"
#include "CameraController.h"
#include "AssimpGUI.h"
#include "Mesh.h"
#include "Model.h"

class App;

class AssimpScene : public Scene {
public:
    unsigned int texId;

    Shader* mpShader_ = nullptr;

    Model* myModel = nullptr;

    CameraController cameraController;

    AssimpGUI mGui_;

    glm::vec3 modelPosition = {0,0,0};
    glm::vec3 modelRotation = {0,0,0};
    glm::vec3 modelScale = {1,1,1};

    AssimpScene(App* theApp);

    void update(const float dt) override;

    void render(Renderer& renderer) override;
};