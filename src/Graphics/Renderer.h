#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteSheet.h"

class Renderer {
private:
    unsigned int mTextureQuadVAO_;
    Shader* mSpriteShader_ = nullptr;
public:
    Renderer();

    void drawSprite(Camera& theCamera);

    void drawSprite(unsigned int textureId, Camera& theCamera, glm::mat4 modelMat);

    void drawSprite(SpriteSheet::Sprite& theSprite, Camera& theCamera, glm::mat4 modelMat);

    // draw line (coords, color, thickness)

    // draw text

    // draw shapes square/circle/triangle (hollow/color/thickness)
};