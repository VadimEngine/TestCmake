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
public:
    struct AttribDetail {
        GLint elements;
        GLenum type;
        GLboolean normalized;
    };

private:
    glm::vec3 mPosition_ = {0.0f, 0.0f, 0.0f};
    glm::vec3 mRotation_ = { 0.0f, 0.0f, 0.0f };
    glm::vec3 mScale_ = { 1.0f, 1.0f, 1.0f };
    glm::vec3 mRotationOrigin_ = {0.0f, 0.0f, 0.0f};

    std::vector<float> mVertices_;

    unsigned int mElementsPerVertex_ = 0;

    Shader* mpShader_ = nullptr;

    unsigned int mVBO_, mVAO_;

    unsigned int mTexId_;

public:
    // TODO set shader in setter instead? Allow making object without a shader??
    ShadedObject(Shader* theShader);

    ~ShadedObject();

    // TODO this should be in model?
    template <typename T>
    void setAttributes(const std::vector<AttribDetail>& attribs);
    
    void setVertices(const std::vector<float>& vertices, const std::vector<float> indices);

    void update(float dt);

    void render(const Camera& theCamera);

    void setPosition(glm::vec3 newPosition);

    void setRotation(glm::vec3 newRotation);

    void setRotationOrigin(glm::vec3 newOrigin);

    void setScale(glm::vec3 newScale);

    void setTexture(unsigned int texId);
};