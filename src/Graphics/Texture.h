#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <unordered_map>
#include <SOIL.h>
#include <stdexcept>
#include "Logger.h"
#include <optional>

class Texture {
private:
    /** Map to hold loaded Textures */
    static std::unordered_map<std::string, unsigned int> sLoadedTextureIdByName_;

public:
    /** Load the preset list of Textures */
    static void loadTextures();
    
    /** 
     * Get a loaded texture Id if it exists
     * \param textureName Name of the loaded texture
     */
    static const std::optional<unsigned int> getLoadedTexture(const std::string& textureName);

    /** Load a texture from a file and return the OpenGL Texture Id */
    static unsigned int loadTexture(const std::string& texturePath);
};