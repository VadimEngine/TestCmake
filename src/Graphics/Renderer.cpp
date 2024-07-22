// class
#include "Renderer.h"

Renderer::Renderer(float screenWidth, float screenHeight, Shader& spriteShader, Shader& text2Shader, Shader& mvpShader, Mesh& rectPlane)
    :mSpriteShader_(spriteShader),
    mMVPShader_(mvpShader),
    mTextShader_(text2Shader),
    mRectPlane_(rectPlane) {
    defaultProjection = glm::ortho(0.0f, static_cast<float>(screenWidth), 0.0f, static_cast<float>(screenHeight));
    // Rect
    float verticesRect[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    // todo use this
    unsigned int indicesRect[] = {
        2, 1, 0,
        0, 3, 2
    };

    unsigned int VBORect, EBORect;

    glGenVertexArrays(1, &mRectVAO_);
    glGenBuffers(1, &VBORect);
    glGenBuffers(1, &EBORect);

    glBindVertexArray(mRectVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBORect);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRect), verticesRect, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBORect);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesRect), indicesRect, GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set up Line properties
    float lineVertices[] = {
        0,0,0,
        0,0,0,
    };

    glGenVertexArrays(1, &mLineVAO_);
    glGenBuffers(1, &mLineVBO_);

    glBindVertexArray(mLineVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, mLineVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_DYNAMIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Create UBO to hold View and Projection matrix
    glGenBuffers(1, &mUBO_);
    glBindBuffer(GL_UNIFORM_BUFFER, mUBO_);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, NULL, GL_STATIC_DRAW);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, mUBO_, 0, 2 * sizeof(glm::mat4));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

Renderer::~Renderer() {}

void Renderer::setCamera(const Camera* camera) {
    glBindBuffer(GL_UNIFORM_BUFFER, mUBO_);

    if (camera != nullptr) {
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(camera->getViewMatrix()));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(camera->getProjectionMatrix()));
    } else {
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(glm::mat4(1)));
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(glm::mat4(1)));
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Renderer::renderSprite(unsigned int textureId, const glm::mat4& modelMat, const glm::vec4& theColor) const {
    mSpriteShader_.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    mSpriteShader_.setMat4("uModel", modelMat);

    // Draw the whole texture
    mSpriteShader_.setInt("uTexture", 0);
    mSpriteShader_.setVec2("uSubImageTopLeft", {0.f, 0.f});
    mSpriteShader_.setVec2("uSubImageSize", {1.f, 1.f});
    mSpriteShader_.setVec4("uColor", theColor);

    mRectPlane_.render(mSpriteShader_);
}

void Renderer::renderSprite(SpriteSheet::Sprite& theSprite, const glm::mat4& modelMat, const glm::vec4& theColor) const {
    mSpriteShader_.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, theSprite.parentSpriteSheet.getTextureId());

    mSpriteShader_.setMat4("uModel", modelMat);
    mSpriteShader_.setInt("uTexture", 0);

    float subImageTopLeftX = static_cast<float>(theSprite.gridIndex.x * theSprite.spriteSize.x) / theSprite.parentSpriteSheet.getSheetSize()[0];
    float subImageTopLeftY = static_cast<float>(theSprite.gridIndex.y * theSprite.spriteSize.y) / theSprite.parentSpriteSheet.getSheetSize()[1];
    mSpriteShader_.setVec2("uSubImageTopLeft", {subImageTopLeftX, subImageTopLeftY});
    float normalWidth = (float)theSprite.spriteSize[0] / (float)theSprite.parentSpriteSheet.getSheetSize()[0];
    float normalHeight = (float)theSprite.spriteSize[1] / (float)theSprite.parentSpriteSheet.getSheetSize()[1];
    mSpriteShader_.setVec2("uSubImageSize", {normalWidth, normalHeight});
    mSpriteShader_.setVec4("uColor", theColor);

    mRectPlane_.render(mSpriteShader_);
}

void Renderer::renderText(const std::string& text, const glm::vec2& position, const Font& font, float scale, const glm::vec3& color) {
    float xPos = position.x;	
    mTextShader_.bind();
    mTextShader_.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(font.getVAO());

    for (const char& c : text) {
        const Font::Character* ch = font.getCharInfo(c);
        if (ch != nullptr) {
            float xpos = xPos + ch->bearing.x * scale;
            float ypos = position.y - (ch->size.y - ch->bearing.y) * scale;

            float w = ch->size.x * scale;
            float h = ch->size.y * scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch->textureId);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, font.getVBO());
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // TODO set only once?
            mTextShader_.setMat4("uModel", glm::mat4(1));
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
            xPos += (ch->advance >> 6) * scale;
        }
    }
}

void Renderer::renderTextCentered(const std::string& text, const glm::vec2& position, const Font& font, float scale, const glm::vec4& color) {
    // activate corresponding render state	
    mTextShader_.bind();
    mTextShader_.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(font.getVAO());

     // Calculate the total width of the text
    float textWidth = 0;

    // Calculate the total width of the text
    float totalWidth = 0.0f;
    for (const char& c : text) {
        const Font::Character* ch = font.getCharInfo(c);
        if (ch != nullptr) {
            totalWidth += (ch->advance >> 6) * scale;
        }
    }

    float startX = position.x - totalWidth / 2.0f;

    // iterate through all characters
    for (const char& c : text) {
        const Font::Character* ch = font.getCharInfo(c);
        if (ch != nullptr) {
            float xpos = startX + ch->bearing.x * scale;
            float ypos = position.y - (ch->size.y - ch->bearing.y) * scale;

            float w = ch->size.x * scale;
            float h = ch->size.y * scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch->textureId);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, font.getVBO());
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            mTextShader_.setMat4("uModel", glm::mat4(1));
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            startX += (ch->advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::renderTextNormalized(const std::string& text, const glm::mat4& modelMat, const Font& font, const glm::vec3& scale, const glm::vec3& color) {
    // activate corresponding render state	
    mTextShader_.bind();
    mTextShader_.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(font.getVAO());

    // Calculate the total width of the text
    float totalWidth = 0.0f;
    for (const char& c : text) {
        const Font::Character* ch = font.getCharInfo(c);
        if (ch != nullptr) {
            totalWidth += (ch->advance >> 6) * scale.x;
        }
    }

    float startX = -totalWidth / 2.0f; // Center horizontally around the origin

    // iterate through all characters
    for (const char& c : text) {
        const Font::Character* ch = font.getCharInfo(c);

        if (ch != nullptr) {
            float xpos = startX + ch->bearing.x * scale.x;
            float ypos = - (ch->size.y - ch->bearing.y) * scale.y; // Adjust for Y-axis to center vertically around the origin

            float w = ch->size.x * scale.x;
            float h = ch->size.y * scale.y;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch->textureId);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, font.getVBO());
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Apply the model matrix to the shader
            mTextShader_.setMat4("uModel", modelMat);

            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            startX += (ch->advance >> 6) * scale.x; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::renderRectangleSimple(const glm::mat4& modelMat, const glm::vec4& theColor) const {
    // TODO fix this
    mMVPShader_.bind();
    mMVPShader_.setMat4("uModel", modelMat);
    mMVPShader_.setVec4("uColor", theColor);

    glBindVertexArray(mRectVAO_);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glBindVertexArray(0);
}

void Renderer::renderLineSimple(const glm::vec3& startPoint, const glm::vec3& endPoint, const glm::mat4& modelMat, const glm::vec4& theColor) const {
    // TODO fix this
    // Update vertices
    float vertices[] = {
        startPoint.x, startPoint.y, startPoint.z,
        endPoint.x, endPoint.y, endPoint.z
    };

    glBindBuffer(GL_ARRAY_BUFFER, mLineVBO_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // draw line
    mMVPShader_.bind();
    mMVPShader_.setMat4("uModel", modelMat);
    mMVPShader_.setVec4("uColor", theColor);

    glBindVertexArray(mLineVAO_);
    glDrawArrays(GL_LINES, 0, 2); // Draw a line using the two vertices

    glBindVertexArray(0);
}