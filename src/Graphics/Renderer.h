#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteSheet.h"

class Renderer {
private:
    /* VAO for a texture quad**/
    unsigned int mTextureQuadVAO_;
    /** Shader for drawing sprites/textures */
    Shader mSpriteShader_;
public:
    /** Constructor */
    Renderer();

    /** Destructor*/
    ~Renderer();

    /**
     * Draw the given Texture with the applied camera and model transforms
     * \param textureId Texture Id to draw
     * \param theCamera Camera to render the Sprite relative to
     * \param modelMat Model matrix to transform the sprite by
     */
    void drawSprite(unsigned int textureId, Camera& theCamera, glm::mat4 modelMat) const;

    /**
     * Draw the given Sprite from a sprite sheet with the applied camera and model transforms
     * \param theSprite The sprite to render
     * \param theCamera Camera to render the Sprite relative to
     * \param modelMat Model matrix to transform the sprite by
     */
    void drawSprite(SpriteSheet::Sprite& theSprite, const Camera& theCamera, const glm::mat4& modelMat) const;

    // draw line (coords, color, thickness)
    // draw text
    // draw shapes square/circle/triangle (hollow/color/thickness)
};