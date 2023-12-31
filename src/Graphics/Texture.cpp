#include "Texture.h"

std::unordered_map<std::string, unsigned int> Texture::sLoadedTextureIdByName_;

/** Load the preset list of Meshes */
void Texture::loadTextures() {
    sLoadedTextureIdByName_["SpriteSheet"] = loadTexture("res/Sprites.png");
    sLoadedTextureIdByName_["SampleTexture"] = loadTexture("res/V.png");
}    

const std::optional<unsigned int> Texture::getLoadedTexture(const std::string& textureName) {
    if (sLoadedTextureIdByName_.find(textureName) != sLoadedTextureIdByName_.end()) {
        return sLoadedTextureIdByName_.find(textureName)->second;
    } else {
        return std::nullopt;
    }
}

unsigned int Texture::loadTexture(const std::string& texturePath) {
    // TODO return option if path fails
    unsigned textureId;
    int width, height;
    int channels;
    // Load image file
    unsigned char* textureData = SOIL_load_image(texturePath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

    if (textureData == nullptr) {
        LOG_E("ERROR LOADING TEXTURE: %s", textureData);
        const char* errorMessage = SOIL_last_result();
        if (errorMessage != nullptr) {
            LOG_E("SOIL error: %s", errorMessage)
        }
        throw std::runtime_error("Shader program linking failed");
    }

    // create textures
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
        (channels == 3) ? GL_RGB : GL_RGBA,
        GL_UNSIGNED_BYTE, textureData
    );
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    SOIL_free_image_data(textureData);
    return textureId;
}