#pragma once
// third party
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
// project
#include "Camera.h"
#include "Font.h"
#include "Mesh.h"
#include "Shader.h"
#include "SpriteSheet.h"
#include "Texture.h"

class Renderer {
public:
    /** Constructor */
    Renderer(float screenWidth, float screenHeight, Shader& spriteShader, Shader& text2Shader, Shader& mvpShader, Mesh& rectPlane);

    /** Destructor*/
    ~Renderer();

    /**
     * Render the given Texture with the applied camera and model transforms
     * @param textureId Texture Id to Render
     * @param theCamera Camera to render the Sprite relative to
     * @param modelMat Model matrix to transform the sprite by
     */
    void renderSprite(unsigned int textureId, Camera& theCamera, const glm::mat4& modelMat, const glm::vec4& theColor = {1,1,1,1}) const;

    /**
     * Render the given Sprite from a sprite sheet with the applied camera and model transforms.
     * @param theSprite The sprite to render
     * @param theCamera Camera to render the Sprite relative to
     * @param modelMat Model matrix to transform the sprite by
     */
    void renderSprite(SpriteSheet::Sprite& theSprite, const Camera& theCamera, const glm::mat4& modelMat, const glm::vec4& theColor = {1,1,1,1}) const;

    /**
     * Render text at the given location. TODO scale.x scale.y
     * @param text The sprite to render
     * @param position Screen position to render (not normalized)
     * @param scale Scale of the text
     * @param color Color of the rendered text
     */
    void renderText(const std::string& text, const glm::vec2& position, const Font& font, float scale, const glm::vec3& color);

    /**
     * @brief Draw text with a transformation and relative to a camera
     *
     * @param text The sprite to render
     * @param modelMat Transformation to apply to the rendering text
     * @param theCamera camera to draw relative to
     * @param font font for the drawn text
     * @param scale Text scale
     * @param color Text color
     */
    void renderTextNormalized(const std::string& text, const glm::mat4& modelMat, const Camera& theCamera, const Font& font, const glm::vec3& scale, const glm::vec3& color);

    /**
     * Render text centered at the given location.
     * @param text The sprite to render
     * @param position Screen position to render (not normalized)
     * @param scale Scale of the text
     * @param color Color of the rendered text
     */
    void renderTextCentered(const std::string& text, const glm::vec2& position, const Font& font, float scale, const glm::vec4& color);

    // Render line (coords, color, thickness)
    // Render shapes square/circle/triangle (hollow/color/thickness)

    void renderRectangleSimple(const Camera& theCamera, const glm::mat4& modelMat, const glm::vec4& theColor) const;

    void renderLineSimple(const glm::vec3& startPoint, const glm::vec3& endPoint, const Camera& theCamera, const glm::mat4& modelMat, const glm::vec4& theColor) const;

private:
    /* VAO for a texture quad **/
    unsigned int mTextureQuadVAO_;
    /** Shader for rendering sprites/textures */
    const Shader& mMVPShader_;
    /** Shader used to render sprites */
    const Shader& mSpriteShader_;
    /** Shader for rendering Texts */
    const Shader& mTextShader_;

    Mesh mRectPlane_;

    unsigned int mRectVAO_;

    unsigned int mLineVAO_;
    unsigned int mLineVBO_;

    glm::mat4 defaultProjection;
};