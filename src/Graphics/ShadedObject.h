#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include <vector>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"

class ShadedObject {
private:
    glm::vec3 mPosition_ = {0.0f, 0.0f, 0.0f};
    glm::vec3 mRotation_ = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mScale_ = { 1.0f, 1.0f, 1.0f };
    glm::vec3 mRotationOrigin_ = {0.0f, 0.0f, 0.0f};

    Model* mModel_= nullptr;
    Shader* mpShader_ = nullptr;
    unsigned int mTexId_;


public:
    // TODO set shader in setter instead? Allow making object without a shader??
    ShadedObject(Shader* theShader);

    ~ShadedObject();

    void setModel(Model* theModel);

    void update(float dt);

    void render(const Camera& theCamera);

    void setPosition(glm::vec3 newPosition);

    void setRotation(glm::vec3 newRotation);

    void setRotationOrigin(glm::vec3 newOrigin);

    void setScale(glm::vec3 newScale);

    void setTexture(unsigned int texId);

    Shader* getShader();
};