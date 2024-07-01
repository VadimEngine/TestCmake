#pragma once
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include <string>
#include <Shader.h>
#include "Camera.h"
#include <filesystem>
#include FT_FREETYPE_H

class Font {
public:
    /**
     * Holds texture information for this font's character
     */
    struct Character {
         // ID handle of the glyph texture
        unsigned int textureId;
        // Size of glyph
        glm::ivec2 size; 
        // Offset from baseline to left/top of glyph
        glm::ivec2 bearing;
         // Horizontal offset to advance to next glyph 
        unsigned int advance;
    };

    /* VAO for a text rendering **/
    unsigned int mTextVAO_;
    /* VBO for a text rendering **/
    unsigned int mTextVBO_;
    /** Character information from the loaded font */
    std::unordered_map<GLchar, Character> mCharacterFrontInfo_;

    /**
     * Construct a new Font object from a tff file
     * 
     * @param fontPath font tff file path
     */
    Font(const std::filesystem::path& fontPath);

    /**
     * Get the Character Info for the given char if it exists
     * 
     * @param theChar char to get character information for
     * @return Character font infomation
     */
    const Character* getCharInfo(GLchar theChar);

    /**
     * Get the VAO for this font 
     */
    unsigned int getVAO();

    /**
     * Get VBO for this font
     */
    unsigned int getVBO();

};