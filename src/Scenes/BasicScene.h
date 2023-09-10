#pragma once
#include "Scene.h"
#include "Shader.h"

class BasicScene : public Scene {
public:

    float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    }; 

    Shader* mpShader_;
    
    unsigned int VBO, VAO;

    BasicScene();

    void update(const float dt) override;
    void render() override;

};