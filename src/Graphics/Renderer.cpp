#include "Renderer.h"

Renderer::Renderer(float screenWidth, float screenHeight)
    : mSpriteShader_(*Shader::getLoadedShader("Texture2d")), mTextShader_(*Shader::getLoadedShader("Text")),
    mTextShader2_(*Shader::getLoadedShader("Text2")) {
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
    // set up font/text resources
    initializeFont(screenWidth, screenHeight);

    // Rect
    float verticesRect[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

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
}

Renderer::~Renderer() {}

void Renderer::renderSprite(unsigned int textureId, Camera& theCamera, glm::mat4 modelMat, const glm::vec4& theColor) const {
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

void Renderer::renderSprite(SpriteSheet::Sprite& theSprite, const Camera& theCamera, const glm::mat4& modelMat, const glm::vec4& theColor) const {
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

void Renderer::renderText(const std::string& text, glm::vec2 position, float scale, const glm::vec3& color) {
    // activate corresponding render state	
    mTextShader_.bind();
    glUniform3f(glGetUniformLocation(mTextShader_.getProgramId(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(mTextVAO_);

    // iterate through all characters
    for (const char& c : text) {
        auto it = mCharacterFrontInfo_.find(c);
        if (it != mCharacterFrontInfo_.end()) {
            Character ch = it->second;

            float xpos = position.x + ch.bearing.x * scale;
            float ypos = position.y - (ch.size.y - ch.bearing.y) * scale;

            float w = ch.size.x * scale;
            float h = ch.size.y * scale;
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
            glBindTexture(GL_TEXTURE_2D, ch.textureId);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, mTextVBO_);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            position.x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::renderTextCentered(const std::string& text, glm::vec2 position, float scale, const glm::vec4& color) {
    // activate corresponding render state	
    mTextShader_.bind();
    mTextShader_.setVec3("textColor", color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(mTextVAO_);
    
     // Calculate the total width of the text
    float textWidth = 0;

    // Calculate the total width of the text
    float totalWidth = 0.0f;
    for (const char& c : text) {
        auto it = mCharacterFrontInfo_.find(c);
        if (it != mCharacterFrontInfo_.end()) {
            Character ch = it->second;
            totalWidth += (ch.advance >> 6) * scale;
        }
    }

    float startX = position.x - totalWidth / 2.0f;

    // iterate through all characters
    for (const char& c : text) {
        auto it = mCharacterFrontInfo_.find(c);
        if (it != mCharacterFrontInfo_.end()) {
            Character ch = it->second;

            float xpos = startX + ch.bearing.x * scale;
            float ypos = position.y - (ch.size.y - ch.bearing.y) * scale;

            float w = ch.size.x * scale;
            float h = ch.size.y * scale;
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
            glBindTexture(GL_TEXTURE_2D, ch.textureId);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, mTextVBO_);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            startX += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::renderTextNormalized(const std::string& text, const glm::mat4& modelMat, const Camera& theCamera, float scale, const glm::vec3& color) const {
    // activate corresponding render state	
    mTextShader2_.bind();
    glUniform3f(glGetUniformLocation(mTextShader2_.getProgramId(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(mTextVAO_);

    // Calculate the total width of the text
    float totalWidth = 0.0f;
    for (const char& c : text) {
        auto it = mCharacterFrontInfo_.find(c);
        if (it != mCharacterFrontInfo_.end()) {
            Character ch = it->second;
            totalWidth += (ch.advance >> 6) * scale;
        }
    }

    float startX = -totalWidth / 2.0f; // Center horizontally around the origin

    // iterate through all characters
    for (const char& c : text) {
        auto it = mCharacterFrontInfo_.find(c);
        if (it != mCharacterFrontInfo_.end()) {
            Character ch = it->second;

            float xpos = startX + ch.bearing.x * scale;
            float ypos = - (ch.size.y - ch.bearing.y) * scale; // Adjust for Y-axis to center vertically around the origin

            float w = ch.size.x * scale;
            float h = ch.size.y * scale;
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
            glBindTexture(GL_TEXTURE_2D, ch.textureId);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, mTextVBO_);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Apply the model matrix to the shader
            //glUniformMatrix4fv(glGetUniformLocation(mTextShader_.getProgramId(), "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
            mTextShader2_.setMat4("model", modelMat);
            mTextShader2_.setMat4("view", theCamera.getViewMatrix());
            mTextShader2_.setMat4("projection", theCamera.getProjectionMatrix());
            
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            startX += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
        }
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Renderer::renderRectangleSimple(const Camera& theCamera, glm::mat4 modelMat, const glm::vec4& theColor) const {
    // TODO use reference to shader
    Shader::getLoadedShader("MVPShader")->bind();
    Shader::getLoadedShader("MVPShader")->setMat4("model", modelMat);
    Shader::getLoadedShader("MVPShader")->setMat4("view", theCamera.getViewMatrix());
    Shader::getLoadedShader("MVPShader")->setMat4("projection", theCamera.getProjectionMatrix());
    Shader::getLoadedShader("MVPShader")->setVec4("uColor", theColor);

    glBindVertexArray(mRectVAO_);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glBindVertexArray(0);
}

void Renderer::renderLineSimple(const glm::vec3& startPoint, const glm::vec3& endPoint, const Camera& theCamera, glm::mat4 modelMat, const glm::vec4& theColor) const {
    // Update vertices
    float vertices[] = {
        startPoint.x, startPoint.y, startPoint.z,
        endPoint.x, endPoint.y, endPoint.z
    };

    glBindBuffer(GL_ARRAY_BUFFER, mLineVBO_);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // draw line
    Shader::getLoadedShader("MVPShader")->bind();
    Shader::getLoadedShader("MVPShader")->setMat4("model", modelMat);
    Shader::getLoadedShader("MVPShader")->setMat4("view", theCamera.getViewMatrix());
    Shader::getLoadedShader("MVPShader")->setMat4("projection", theCamera.getProjectionMatrix());
    Shader::getLoadedShader("MVPShader")->setVec4("uColor", theColor);
    
    glBindVertexArray(mLineVAO_);
    glDrawArrays(GL_LINES, 0, 2); // Draw a line using the two vertices

    glBindVertexArray(0);
}

void Renderer::initializeFont(float screenWidth, float screenHeight) {
    // TODO get actual screen dimensions
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(screenWidth), 0.0f, static_cast<float>(screenHeight));
    mTextShader_.bind();
    glUniformMatrix4fv(glGetUniformLocation(mTextShader_.getProgramId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        LOG_E("ERROR::FREETYPE: Could not init FreeType Library");
    }

    FT_Face face;
    if (FT_New_Face(ft, "Res/fonts/Consolas.ttf", 0, &face)) {
        LOG_E("ERROR::FREETYPE: Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // load first 128 characters of ASCII set
    for (unsigned char c = 0; c < 128; c++) {
        // Load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            LOG_E("ERROR::FREETYTPE: Failed to load Glyph");
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        mCharacterFrontInfo_.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &mTextVAO_);
    glGenBuffers(1, &mTextVBO_);
    glBindVertexArray(mTextVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, mTextVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
