#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteSheet.h"
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <unordered_map>
#include <ft2build.h>
#include FT_FREETYPE_H

class Renderer {
private:
    struct Character {
        unsigned int textureId; // ID handle of the glyph texture
        glm::ivec2   size;      // Size of glyph
        glm::ivec2   bearing;   // Offset from baseline to left/top of glyph
        unsigned int advance;   // Horizontal offset to advance to next glyph
    };
    /* VAO for a texture quad **/
    unsigned int mTextureQuadVAO_;
    /* VAO for a text rendering **/
    unsigned int mTextVAO_;
    /* VBO for a text rendering **/
    unsigned int mTextVBO_;
    /** Shader for rendering sprites/textures */
    const Shader& mSpriteShader_;
    /** Shader for rendering Texts */
    const Shader& mTextShader_;

    const Shader& mTextShader2_;

    /** Map of character font information */
    std::unordered_map<GLchar, Character> mCharacterFrontInfo_;


    unsigned int mRectVAO_;

    unsigned int mLineVAO_;
    unsigned int mLineVBO_;

public:
    /** Constructor */
    Renderer(float screenWidth, float screenHeight);

    /** Destructor*/
    ~Renderer();

    /**
     * Render the given Texture with the applied camera and model transforms
     * \param textureId Texture Id to Render
     * \param theCamera Camera to render the Sprite relative to
     * \param modelMat Model matrix to transform the sprite by
     */
    void renderSprite(unsigned int textureId, Camera& theCamera, glm::mat4 modelMat, const glm::vec4& theColor = {1,1,1,1}) const;

    /**
     * Render the given Sprite from a sprite sheet with the applied camera and model transforms.
     * \param theSprite The sprite to render
     * \param theCamera Camera to render the Sprite relative to
     * \param modelMat Model matrix to transform the sprite by
     */
    void renderSprite(SpriteSheet::Sprite& theSprite, const Camera& theCamera, const glm::mat4& modelMat, const glm::vec4& theColor = {1,1,1,1}) const;

    /**
     * Render text at the given location. TODO scale.x scale.y
     * \param text The sprite to render
     * \param position Screen position to render (not normalized)
     * \param scale Scale of the text
     * \param color Color of the rendered text
     */
    void renderText(const std::string& text, glm::vec2 position, float scale, const glm::vec3& color);

    void renderTextNormalized(const std::string& text, const glm::mat4& modelMat, const Camera& theCamera, float scale, const glm::vec3& color) const;


    /**
     * Render text centered at the given location. TODO scale.x scale.y
     * \param text The sprite to render
     * \param position Screen position to render (not normalized)
     * \param scale Scale of the text
     * \param color Color of the rendered text 
     */
    void renderTextCentered(const std::string& text, glm::vec2 position, float scale, const glm::vec4& color);

    // Render line (coords, color, thickness)
    // Render shapes square/circle/triangle (hollow/color/thickness)

    void renderRectangleSimple(const Camera& theCamera, glm::mat4 modelMat, const glm::vec4& theColor) const;

    void renderLineSimple(const glm::vec3& startPoint, const glm::vec3& endPoint, const Camera& theCamera, glm::mat4 modelMat, const glm::vec4& theColor) const;

private:
    /** Load font and shaders for rendering Text */
    void initializeFont(float screenWidth, float screenHeight);
};