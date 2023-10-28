#include "Renderer.h"

Renderer::Renderer()
    : mSpriteShader_(*Shader::getLoadedShader("Texture2d")) {
    // initialize sprite renderer
    GLuint VBO;

    GLfloat vertices[] = {
        // position     // uv
        -.5f, -.5f, 0.0f, 0.0f, 0.0f,
        .5f, -.5f, 0.0f, 1.0f, 0.0f,
        -.5f, .5f, 0.0f, 0.0f, 1.0f,

        .5f, -.5f, 0.0f, 1.0f, 0.0f,
        .5f, .5f, 0.0f, 1.0f, 1.0f,
        -.5f, .5f, 0.0f, 0.0f, 1.0f,
    };

    glGenVertexArrays(1, &mTextureQuadVAO_);
    glGenBuffers(1, &VBO);

    glBindVertexArray(mTextureQuadVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    
    // vertex texture coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Bind the uniform "theTexture" to GL_TEXTURE0
    mSpriteShader_.bind();
    mSpriteShader_.setInt("theTexture", 0);
}

Renderer::~Renderer() {}

void Renderer::drawSprite(unsigned int textureId, Camera& theCamera, glm::mat4 modelMat, const glm::vec4& theColor) const {
    mSpriteShader_.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    mSpriteShader_.setMat4("model", modelMat);
    mSpriteShader_.setMat4("view", theCamera.getViewMatrix());
    mSpriteShader_.setMat4("projection", theCamera.getProjectionMatrix());
    // Draw the whole texture
    mSpriteShader_.setBool("uDrawSubImage", false);
    mSpriteShader_.setVec4("uColor", theColor);

    glBindVertexArray(mTextureQuadVAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::drawSprite(SpriteSheet::Sprite& theSprite, const Camera& theCamera, const glm::mat4& modelMat, const glm::vec4& theColor) const {
    mSpriteShader_.bind();

    glBindTexture(GL_TEXTURE_2D, theSprite.parentSpriteSheet->getTextureId());
    mSpriteShader_.setMat4("model", modelMat);
    mSpriteShader_.setMat4("view", theCamera.getViewMatrix());
    mSpriteShader_.setMat4("projection", theCamera.getProjectionMatrix());
    mSpriteShader_.setBool("uDrawSubImage", true);
    mSpriteShader_.setVec2("uSpriteGridIndex", theSprite.gridIndex);
    mSpriteShader_.setVec2("uSheetSize", theSprite.parentSpriteSheet->getSheetSize());
    mSpriteShader_.setVec2("uSpriteSize", theSprite.spriteSize);
    mSpriteShader_.setVec4("uColor", theColor);

    glBindVertexArray(mTextureQuadVAO_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
